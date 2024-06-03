
LuaCEmbedResponse *tree_find(LuaCEmbedTable *self, LuaCEmbed *args){
    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);

    for(int i =0; i < self_tree->size;i++){
        LuaCEmbedTable *tree_part = create_tree_part_reference(args,self_tree->tree_parts[i]);
        LuaCEmbedTable *args_to_call = lua.tables.new_anonymous_table(args);
        lua.tables.append_table(args_to_call,tree_part);
        LuaCEmbedTable *response = lua.args.run_lambda(args,0,args_to_call,1);
        if(lua.has_errors(args)){
            char *error_msg = lua.get_error_message(args);
            return lua.response.send_error(error_msg);
        }
        int response_type =lua.tables.get_type_by_index(response,0);
        if(response_type != lua.types.NILL){
            bool is_the_value = lua.tables.get_bool_by_index(response,0);
            if(lua.has_errors(args)){
                char *error_msg = lua.get_error_message(args);
                return lua.response.send_error(error_msg);
            }

            if(is_the_value){
                return  lua.response.send_table(tree_part);
            }
        }
    }
    return NULL;
}


LuaCEmbedResponse *tree_count(LuaCEmbedTable *self, LuaCEmbed *args){
    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);
    long total = 0;
    for(int i =0; i < self_tree->size;i++){
        LuaCEmbedTable *tree_part = create_tree_part_reference(args,self_tree->tree_parts[i]);
        LuaCEmbedTable *args_to_call = lua.tables.new_anonymous_table(args);
        lua.tables.append_table(args_to_call,tree_part);
        LuaCEmbedTable *response = lua.args.run_lambda(args,0,args_to_call,1);
        if(lua.has_errors(args)){
            char *error_msg = lua.get_error_message(args);
            return lua.response.send_error(error_msg);
        }
        int response_type =lua.tables.get_type_by_index(response,0);
        if(response_type != lua.types.NILL){
            bool is_the_value = lua.tables.get_bool_by_index(response,0);
            if(lua.has_errors(args)){
                char *error_msg = lua.get_error_message(args);
                return lua.response.send_error(error_msg);
            }

            if(is_the_value){
                total+=1;
            }
        }

    }
    return lua.response.send_long(total);
}


LuaCEmbedResponse *tree_map(LuaCEmbedTable *self, LuaCEmbed *args){

    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);
    LuaCEmbedTable *final_map = lua.tables.new_anonymous_table(args);

    for(int i =0; i < self_tree->size;i++){
        LuaCEmbedTable *tree_part = create_tree_part_reference(args,self_tree->tree_parts[i]);
        LuaCEmbedTable *args_to_call = lua.tables.new_anonymous_table(args);
        lua.tables.append_table(args_to_call,tree_part);
        LuaCEmbedTable *response = lua.args.run_lambda(args,0,args_to_call,1);
        if(lua.has_errors(args)){
            char *error_msg = lua.get_error_message(args);
            return lua.response.send_error(error_msg);
        }
        int response_type =lua.tables.get_type_by_index(response,0);
        if(response_type!= LUA_CEMBED_NIL && response_type != LUA_CEMBED_NOT_FOUND){
            lua.tables.append_evaluation(final_map,"%s[1]",response->global_name);
        }

    }
    return lua.response.send_table(final_map);
}




LuaCEmbedResponse *tree_foreach(LuaCEmbedTable *self, LuaCEmbed *args){

    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);

    for(int i =0; i < self_tree->size;i++){
        LuaCEmbedTable *tree_part = create_tree_part_reference(args,self_tree->tree_parts[i]);
        LuaCEmbedTable *args_to_call = lua.tables.new_anonymous_table(args);
        lua.tables.append_table(args_to_call,tree_part);
        lua.args.run_lambda(args,0,args_to_call,1);
        if(lua.has_errors(args)){
            char *error_msg = lua.get_error_message(args);
            return lua.response.send_error(error_msg);
        }

    }
    return NULL;
}
