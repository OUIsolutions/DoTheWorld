


LuaCEmbedResponse * generate_sha_from_string(LuaCEmbedTable *self,LuaCEmbed *args){
    char *content = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    char *result = dtw.generate_sha_from_string(content);
    LuaCEmbedResponse *response = lua.response.send_str(result);
    free(result);
    return  response;
}


LuaCEmbedResponse * generate_sha_from_folder(LuaCEmbedTable *self,LuaCEmbed *args){
    char *folder = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
    if(dtw.entity_type(folder) != DTW_FOLDER_TYPE){
        return lua.response.send_error("its not a folder");
    }
    DtwHash *hash = dtw.hash.newHash();
    dtw.hash.digest_folder_by_content(hash,folder);
    LuaCEmbedResponse *response = lua.response.send_str(hash->hash);
    dtw.hash.free(hash);
    return response;
}

LuaCEmbedResponse * generate_sha_from_file(LuaCEmbedTable *self,LuaCEmbed *args){
    char *path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_msg = lua.get_error_message(args);
        return lua.response.send_error(error_msg);
    }
   char *sha= dtw.generate_sha_from_file(path);
    if(sha== NULL){
        return lua.response.send_error("its not a file");
    }
    LuaCEmbedResponse *response = lua.response.send_str(sha);
    free(sha);
    return response;
}