
LuaCEmbedResponse * generate_exit(LuaCEmbedTable *self,LuaCEmbed *args){
    int status = lua.args.get_long(args,0);
    if(lua.has_errors(args)){
        char *menssage = lua.get_error_message(args);
        return  lua.response.send_error(menssage);
    }
    lua_exit = status;
    return lua.response.send_error("");
}

LuaCEmbedResponse * extract_dir(LuaCEmbedTable *self,LuaCEmbed *args){
    char *pathstr = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    DtwPath *path = dtw.path.newPath(pathstr);
    char *dir =  dtw.path.get_dir(path);
    if(dir== NULL){
        dtw.path.free(path);
        return lua.response.send_str("");
    }
    LuaCEmbedResponse *response = lua.response.send_str(dir);
    dtw.path.free(path);
    return  response;
}


LuaCEmbedResponse * concat_path(LuaCEmbedTable *self,LuaCEmbed *args){
    char *path = lua.args.get_str(args,0);
    char *path_to_concat = lua.args.get_str(args,1);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    char *value = dtw.concat_path(path,path_to_concat);
    LuaCEmbedResponse *response  =lua.response.send_str(value);
    free(value);
    return response;
}
