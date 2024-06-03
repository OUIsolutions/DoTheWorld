
LuaCEmbedResponse * create_tree_from_json_tree_string(LuaCEmbed *args){
    char *content = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    UniversalGarbage *garbage =  newUniversalGarbage();
    DtwTree *tree = dtw.tree.newTree();
    UniversalGarbage_add_return(garbage,dtw.tree.free,tree);

   bool result = dtw.tree.loads_json_tree(tree,content);

    if(result ==false){
        dtw.tree.free(tree);
        DtwJsonTreeError *error_tree = dtw.tree.json_error.validate_json_tree_by_content(content);
        UniversalGarbage_add(garbage,dtw.tree.json_error.free,error_tree);

        LuaCEmbedResponse *response = lua.response.send_error(
            "%s at index %d",
                error_tree->menssage,
                error_tree->position
            );
        UniversalGarbage_free_including_return(garbage);
        return response;
    }
    LuaCEmbedTable * self = raw_create_tree(args,tree);
    UniversalGarbage_free(garbage);
    return lua.response.send_table(self);
}

LuaCEmbedResponse * create_tree_from_json_tree_file(LuaCEmbed *args){

    char *path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    UniversalGarbage *garbage = newUniversalGarbage();

    char *content = dtw.load_string_file_content(path);
    UniversalGarbage_add_simple(garbage,content);
    if(content == NULL){
        UniversalGarbage_free(garbage);
        return lua.response.send_error(FILE_NOT_FOUND,path);
    }

    DtwTree *tree = dtw.tree.newTree();
    UniversalGarbage_add_return(garbage,dtw.tree.free,tree);

    bool result = dtw.tree.loads_json_tree(tree,content);

    if(result ==false){
        dtw.tree.free(tree);
        DtwJsonTreeError *error_tree = dtw.tree.json_error.validate_json_tree_by_content(content);
        UniversalGarbage_add(garbage,dtw.tree.json_error.free,error_tree);
        LuaCEmbedResponse *response = lua.response.send_error(
            "%s at index %d",
                error_tree->menssage,
                error_tree->position
            );

        UniversalGarbage_free_including_return(garbage);
        return response;
    }
    LuaCEmbedTable * self = raw_create_tree(args,tree);
    UniversalGarbage_free(garbage);
    return lua.response.send_table(self);
}


LuaCEmbedResponse *tree_dump_to_json_string(LuaCEmbedTable *self, LuaCEmbed *args){
    LuaCEmbedTable *props_table = NULL;
    if(lua.args.get_type(args,0) != lua.types.NILL){
        props_table = lua.args.get_table(args,0);
    }
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }

    DtwTreeProps props = create_tree_props(props_table);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);
    char *result = dtw.tree.dumps_json_tree(self_tree,props);
    LuaCEmbedResponse *response = lua.response.send_str(result);
    free(result);
    return  response;
}

LuaCEmbedResponse *tree_dump_to_json_file(LuaCEmbedTable *self, LuaCEmbed *args){
    char *path = lua.args.get_str(args,0);
    LuaCEmbedTable *props_table = NULL;
    if(lua.args.get_type(args,1) != lua.types.NILL){
        props_table = lua.args.get_table(args,1);
    }
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }

    DtwTreeProps props = create_tree_props(props_table);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);
    dtw.tree.dumps_json_tree_to_file(self_tree,path,props);
    return  lua.response.send_table(self);
}