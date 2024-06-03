
LuaCEmbedResponse  * aply_listage(LuaCEmbed *args,DtwStringArray* (*callback)(const char *folder,bool concat_path)){
    char *source = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    bool concat_path = false;
    if(lua.args.size(args) >= 2){
        concat_path = lua.args.get_bool(args,1);
    }
    DtwStringArray * listage = callback(source,concat_path);
    dtw.string_array.sort(listage);
    LuaCEmbedTable * table = lua.tables.new_anonymous_table(args);
    for(int i = 0; i < listage->size; i++){
        char * current_value = listage->strings[i];
        lua.tables.append_string(table,current_value);
    }

    dtw.string_array.free(listage);
    return lua.response.send_table(table);
}

LuaCEmbedResponse  * list_files(LuaCEmbed *args){
    return aply_listage(args,dtw.list_files);
}

LuaCEmbedResponse  * list_dirs(LuaCEmbed *args){
    return aply_listage(args,dtw.list_dirs);

}

LuaCEmbedResponse  * list_all(LuaCEmbed *args){
    return aply_listage(args,dtw.list_all);
}

LuaCEmbedResponse  * list_files_recursively(LuaCEmbed *args){
   return aply_listage(args,dtw.list_files_recursively);
}

LuaCEmbedResponse  * list_dirs_recursively(LuaCEmbed *args){
    return aply_listage(args,dtw.list_dirs_recursively);
}

LuaCEmbedResponse  * list_all_recursively(LuaCEmbed *args){
    return aply_listage(args,dtw.list_all_recursively);
}
