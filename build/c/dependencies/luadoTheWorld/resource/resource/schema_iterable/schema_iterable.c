
LuaCEmbedResponse * schema_list_resources(LuaCEmbedTable *self,LuaCEmbed *args){
    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResourceArray  *elements = dtw.resource.sub_resources(resource->values_resource);
    LuaCEmbedTable *response = lua.tables.new_anonymous_table(args);
    for(int i = 0; i < elements->size; i++) {
        DtwResource*current = elements->resources[i];
        LuaCEmbedTable  *sub = raw_create_resource(args,current);
        lua.tables.append_table(response,sub);
    }
    return lua.response.send_table(response);
}

LuaCEmbedResponse * schema_find_resource(LuaCEmbedTable *self,LuaCEmbed *args){

    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResourceArray  *elements = dtw.resource.sub_resources(resource->values_resource);
    for(int i = 0; i < elements->size; i++) {
        DtwResource*current = elements->resources[i];
        LuaCEmbedTable  *sub = raw_create_resource(args,current);

        LuaCEmbedTable *args_to_callback = lua.tables.new_anonymous_table(args);
        lua.tables.append_table(args_to_callback,sub);
        LuaCEmbedTable  *user_response = lua.args.run_lambda(args,0,args_to_callback,1);

        if(lua.has_errors(args)){
            char *error = lua.get_error_message(args);
            return lua.response.send_error(error);
        }

        bool possible_return = lua.tables.get_bool_by_index(user_response,0);
        if(possible_return){
            return lua.response.send_table(sub);
        }
    }

    return NULL;
}



LuaCEmbedResponse * schema_count_resource(LuaCEmbedTable *self,LuaCEmbed *args){
    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResourceArray  *elements = dtw.resource.sub_resources(resource->values_resource);
    long size = 0;
    for(int i = 0; i < elements->size; i++) {
        DtwResource*current = elements->resources[i];
        LuaCEmbedTable  *sub = raw_create_resource(args,current);

        LuaCEmbedTable *args_to_callback = lua.tables.new_anonymous_table(args);
        lua.tables.append_table(args_to_callback,sub);
        LuaCEmbedTable  *user_response = lua.args.run_lambda(args,0,args_to_callback,1);

        if(lua.has_errors(args)){
            char *error = lua.get_error_message(args);
            return lua.response.send_error(error);
        }

        bool possible_return = lua.tables.get_bool_by_index(user_response,0);
        if(possible_return){
            size+=1;
        }
    }

    return lua.response.send_long(size);
}

LuaCEmbedResponse * schema_map_resource(LuaCEmbedTable *self,LuaCEmbed *args){
    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResourceArray  *elements = dtw.resource.sub_resources(resource->values_resource);
    LuaCEmbedTable *response = lua.tables.new_anonymous_table(args);

    for(int i = 0; i < elements->size; i++) {
        DtwResource*current = elements->resources[i];
        LuaCEmbedTable  *sub = raw_create_resource(args,current);

        LuaCEmbedTable *args_to_callback = lua.tables.new_anonymous_table(args);
        lua.tables.append_table(args_to_callback,sub);
        LuaCEmbedTable  *user_response = lua.args.run_lambda(args,0,args_to_callback,1);

        if(lua.has_errors(args)){
            char *error = lua.get_error_message(args);
            return lua.response.send_error(error);
        }
        long size = lua.tables.get_size(user_response);
        if(size ==1){
            lua.tables.append_evaluation(response,"%s[1]",user_response->global_name);
        }


    }

    return lua.response.send_table(response);
}

LuaCEmbedResponse * resource_schema_each(LuaCEmbedTable *self, LuaCEmbed *args){
    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResourceArray  *elements = dtw.resource.get_schema_values(resource);

    if(dtw.resource.error(resource)){
        char *message = dtw.resource.get_error_message(resource);
        return lua.response.send_error(message);
    }

    for(int i = 0; i < elements->size; i++) {
        DtwResource*current = elements->resources[i];
        LuaCEmbedTable  *sub = raw_create_resource(args,current);
        LuaCEmbedTable *args_to_callback = lua.tables.new_anonymous_table(args);
        lua.tables.append_table(args_to_callback,sub);
        lua.args.run_lambda(args,0,args_to_callback,0);
    }
    if(lua.has_errors(args)){
        printf("%s\n",lua.get_error_message(args));
    }

    return NULL;
}
