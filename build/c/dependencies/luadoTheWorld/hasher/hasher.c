
LuaCEmbedResponse * hasher_digest_file(LuaCEmbedTable *self,LuaCEmbed *args){
    char *filename = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }

    DtwHash *hash = (DtwHash*)lua.tables.get_long_prop(self,HASH_POINTER);
    if(!dtw.hash.digest_file(hash,filename)){
        char *file_not_found = private_LuaCembed_format(FILE_NOT_FOUND,filename);
        LuaCEmbedResponse *response = lua.response.send_error(file_not_found);
        free(file_not_found);
        return response;
    }
    return NULL;
}

LuaCEmbedResponse * hasher_digest_folder_by_content(LuaCEmbedTable *self, LuaCEmbed *args){
    char *folder = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }

    DtwHash *hash = (DtwHash*)lua.tables.get_long_prop(self,HASH_POINTER);
    if(!dtw.hash.digest_folder_by_content(hash,folder)){
        char *folder_not_found = private_LuaCembed_format(FOLDER_NOT_FOUND,folder);
        LuaCEmbedResponse *response = lua.response.send_error(folder_not_found);
        free(folder_not_found);
        return response;
    }
    return NULL;
}

LuaCEmbedResponse * hasher_digest_folder_by_last_modification(LuaCEmbedTable *self, LuaCEmbed *args){
    char *folder = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }


    DtwHash *hash = (DtwHash*)lua.tables.get_long_prop(self,HASH_POINTER);
    if(!dtw.hash.digest_folder_by_last_modification(hash,folder)){
        char *folder_not_found = private_LuaCembed_format(FOLDER_NOT_FOUND,folder);
        LuaCEmbedResponse *response = lua.response.send_error(folder_not_found);
        free(folder_not_found);
        return response;
    }
    return NULL;
}



LuaCEmbedResponse * delete_hasher(LuaCEmbedTable *self,LuaCEmbed *args){
    DtwHash *hash = (DtwHash*)lua.tables.get_long_prop(self,HASH_POINTER);
    dtw.hash.free(hash);
    return NULL;
}

LuaCEmbedResponse * hasher_digest(LuaCEmbedTable *self,LuaCEmbed *args){
    Writeble write_obj = create_writeble(args,0);
    if(write_obj.error){
        return write_obj.error;
    }
    DtwHash *hash = (DtwHash*)lua.tables.get_long_prop(self,HASH_POINTER);
    dtw.hash.digest_any(hash,write_obj.content,write_obj.size);
    Writeble_free(&write_obj);
    return NULL;
}

LuaCEmbedResponse * hasher_get_value(LuaCEmbedTable *self,LuaCEmbed *args){
    DtwHash *hash = (DtwHash*)lua.tables.get_long_prop(self,HASH_POINTER);
    return lua.response.send_str(hash->hash);
}


LuaCEmbedResponse * create_hasher(LuaCEmbed *args){
    LuaCEmbedTable * self = lua.tables.new_anonymous_table(args);
    DtwHash *hash = newDtwHash();
    lua.tables.set_long_prop(self,HASH_POINTER,(long long)hash);
    lua.tables.set_method(self, DIGESST_METHOD, hasher_digest);
    lua.tables.set_method(self, TO_STRING_METHOD, hasher_get_value);
    lua.tables.set_method(self, GET_VALUE_METHOD, hasher_get_value);
    lua.tables.set_method(self, DIGESST_FILE_METHOD, hasher_digest_file);
    lua.tables.set_method(self, DIGESST_FOLDER_BY_CONTENT_METHOD, hasher_digest_folder_by_content);
    lua.tables.set_method(self, DIGESST_FOLDER_BY_LAST_MODIFICATION_METHOD, hasher_digest_folder_by_last_modification);
    lua.tables.set_method(self, DELETE_METHOD, delete_hasher);
    return lua.response.send_table(self);
}
