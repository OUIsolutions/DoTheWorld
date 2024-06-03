

LuaCEmbedResponse * tree_part_get_value(LuaCEmbedTable *self,LuaCEmbed *args){
    DtwTreePart *self_part  = (DtwTreePart*)lua.tables.get_long_prop(self,TREE_PART_POINTER);
    
}


LuaCEmbedResponse * tree_part_set_value(LuaCEmbedTable *self,LuaCEmbed *args){
    return NULL;
}

LuaCEmbedResponse * tree_part_hardware_remove(LuaCEmbedTable *self,LuaCEmbed *args){
    return NULL;
}

LuaCEmbedResponse * tree_part_hardware_write(LuaCEmbedTable *self,LuaCEmbed *args){
    return NULL;
}

LuaCEmbedResponse * tree_part_hardware_modify(LuaCEmbedTable *self,LuaCEmbed *args){
    return NULL;
}

LuaCEmbedResponse * tree_part_get_content_sha(LuaCEmbedTable *self,LuaCEmbed *args){
    return NULL;
}

LuaCEmbedResponse * tree_part_unload_content(LuaCEmbedTable *self,LuaCEmbed *args){
    return NULL;
}

LuaCEmbedResponse * tree_part_load_content(LuaCEmbedTable *self,LuaCEmbed *args){
    return NULL;
}



LuaCEmbedTable * create_tree_part_reference(LuaCEmbed *args,DtwTreePart *part){
    LuaCEmbedTable *self = lua.tables.new_anonymous_table(args);
    lua.tables.set_long_prop(self,TREE_PART_POINTER,(long long)part);
    LuaCEmbedTable *path = create_path_reference(args,part->path);
    lua.tables.set_sub_table_prop(self,PATH_PROPS,path);
    lua.tables.set_method(self,GET_VALUE_METHOD,tree_part_get_value);
    lua.tables.set_method(self,SET_VALUE_METHOD,tree_part_set_value);
    lua.tables.set_method(self,HARDWARE_REMOVE_METHOD,tree_part_hardware_remove);
    lua.tables.set_method(self,HARDWARE_MODIFY_METHOD,tree_part_hardware_modify);
    lua.tables.set_method(self,GET_SHA_METHOD,tree_part_get_content_sha);
    lua.tables.set_method(self,UNLOAD_METHOD,tree_part_unload_content);
    lua.tables.set_method(self,LOAD_METHOD,tree_part_load_content);
    return self;
}



