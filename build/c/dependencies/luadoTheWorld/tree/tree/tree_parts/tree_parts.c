
LuaCEmbedResponse *new_tree_part(LuaCEmbedTable *self, LuaCEmbed *args){
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
    DtwTreePart *tree_part = dtw.tree.part.newPartLoading(path);
    dtw.tree.add_tree_part_getting_owenership(self_tree,tree_part);
    LuaCEmbedTable *tree_part_table = create_tree_part_reference(args,tree_part);
    return lua.response.send_table(tree_part_table);
}

LuaCEmbedResponse *new_tree_part_loading(LuaCEmbedTable *self, LuaCEmbed *args){
    char *path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);
    DtwTreePart *tree_part = dtw.tree.part.newPartLoading(path);
    dtw.tree.add_tree_part_getting_owenership(self_tree,tree_part);
    LuaCEmbedTable *tree_part_table = create_tree_part_reference(args,tree_part);
    return lua.response.send_table(tree_part_table);
}

LuaCEmbedResponse *new_tree_part_empty(LuaCEmbedTable *self, LuaCEmbed *args){

    char *path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);
    DtwTreePart *tree_part = dtw.tree.part.newPartEmpty(path);
    dtw.tree.add_tree_part_getting_owenership(self_tree,tree_part);
    LuaCEmbedTable *tree_part_table = create_tree_part_reference(args,tree_part);
    return lua.response.send_table(tree_part_table);
}

LuaCEmbedResponse *get_tree_part_by_index(LuaCEmbedTable *self, LuaCEmbed *args){

    long index = lua.args.get_long(args,0)-1;
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }

    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);
    if(index>=self_tree->size){
        return NULL;
    }

    LuaCEmbedTable *result  = create_tree_part_reference(args,self_tree->tree_parts[index]);
    return  lua.response.send_table(result);
}



LuaCEmbedResponse *tree_get_tree_part_by_name(LuaCEmbedTable *self, LuaCEmbed *args){
    char *name = lua.args.get_str(args,0);

    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }

    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);
    DtwTreePart * possible = dtw.tree.find_tree_part_by_name(self_tree,name);
    if(possible == NULL){
        return NULL;
    }
    LuaCEmbedTable *created_table = create_tree_part_reference(args,possible);
    return lua.response.send_table(created_table);
}



LuaCEmbedResponse *tree_get_tree_part_by_path(LuaCEmbedTable *self, LuaCEmbed *args){
    char *path = lua.args.get_str(args,0);

    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }

    DtwTree *self_tree = (DtwTree*)lua.tables.get_long_prop(self,TREE_POINTER);
    DtwTreePart * possible = dtw.tree.find_tree_part_by_path(self_tree,path);
    if(possible == NULL){
        return NULL;
    }
    LuaCEmbedTable *created_table = create_tree_part_reference(args,possible);
    return lua.response.send_table(created_table);
}

