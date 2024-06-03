//
// Created by mateusmoutinho on 22/05/24.
//
LuaCEmbedResponse  * Resource_new_insertion(LuaCEmbedTable *self, LuaCEmbed *args){
    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResource  *created = dtw.resource.new_schema_insertion(resource);
    LuaCEmbedTable  *sub = raw_create_resource(args,created);
    if(dtw.resource.error(resource)){
        char *message = dtw.resource.get_error_message(resource);
        return lua.response.send_error(message);
    }

    return lua.response.send_table(sub);
}


LuaCEmbedResponse  * get_resource_match_schema_by_primary_key(LuaCEmbedTable *self, LuaCEmbed *args){
    char *key = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    Writeble  write_obj = create_writeble(args,1);
    if(write_obj.error){
        return write_obj.error;
    }
    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);

    DtwResource *founded = dtw.resource.find_by_primary_key_with_binary(resource,key,write_obj.content,write_obj.size);
    if(dtw.resource.error(resource)){
        char *message = dtw.resource.get_error_message(resource);
        return lua.response.send_error(message);
    }
    if(!founded){
        return NULL;
    }
    LuaCEmbedTable  *sub = raw_create_resource(args,founded);
    return lua.response.send_table(sub);
}


LuaCEmbedResponse  * get_resource_by_name_id(LuaCEmbedTable *self, LuaCEmbed *args){
    char *name_id = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }


    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResource *founded = dtw.resource.find_by_name_id(resource,name_id);
    if(dtw.resource.error(resource)){
        char *message = dtw.resource.get_error_message(resource);
        return lua.response.send_error(message);
    }
    if(!founded){
        return NULL;
    }
    
    LuaCEmbedTable  *sub = raw_create_resource(args,founded);

    return lua.response.send_table(sub);
}

LuaCEmbedResponse  * dangerous_rename_schema_prop(LuaCEmbedTable *self,LuaCEmbed *args){
    char *key = lua.args.get_str(args,0);
    char *new_name = lua.args.get_str(args,1);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }


    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    dtw.resource.dangerous_rename_schema_prop(resource,key,new_name);
    if(dtw.resource.error(resource)){
        char *message = dtw.resource.get_error_message(resource);
        return lua.response.send_error(message);
    }
    return lua.response.send_table(self);
}

LuaCEmbedResponse  * dangerous_remove_schema_prop(LuaCEmbedTable *self,LuaCEmbed *args){
    char *key_to_remove = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }

    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    dtw.resource.dangerous_remove_schema_prop(resource,key_to_remove);
    if(dtw.resource.error(resource)){
        char *message = dtw.resource.get_error_message(resource);
        return lua.response.send_error(message);
    }
    return lua.response.send_table(self);
}

LuaCEmbedResponse  * Resource_new_schema(LuaCEmbedTable *self, LuaCEmbed *args){
    DtwResource *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwSchema  *schema = dtw.resource.newSchema(resource);
    LuaCEmbedTable *created_table = raw_create_schema(args,schema);
    if(dtw.resource.error(resource)){
        char *message = dtw.resource.get_error_message(resource);
        return lua.response.send_error(message);
    }
    return lua.response.send_table(created_table);
}

