LuaCEmbedResponse *custom_print(LuaCEmbedTable *self,LuaCEmbed *args){

    int size = lua.args.size(args);
    for(int i = 0; i < size; i++){
        int type = lua.args.get_type(args,i);
        if(type == lua.types.NUMBER){
            printf("%lf",lua.args.get_double(args,i));
        }
        if(type == lua.types.STRING){
            printf("%s",lua.args.get_str(args,i));
        }
        if(type == lua.types.BOOL){
            char *bool_str = lua.args.get_bool(args,i) ? "true":"false";
            printf("%s",bool_str);
        }

        if(type == lua.types.NILL){
            printf("nil");
        }
    }
    return NULL;
}

LuaCEmbedResponse *lua_load_string(LuaCEmbedTable *self,LuaCEmbed *args){
    char *filename = lua.args.get_str(args,0);

    if(lua.has_errors(args)){
        char *erro_msg = lua.get_error_message(args);
        return lua.response.send_error(erro_msg);
    }
    bool is_binary;
    long size;
    unsigned char *content = dtw.load_any_content(filename,&size,&is_binary);
    if(is_binary){
        return lua.response.send_error("file %s its a binary",filename);
    }
    if(content == NULL){
        if(dtw.entity_type(filename) == DTW_FILE_TYPE){
            return lua.response.send_str("");
        }
        return lua.response.send_error("file %s not found",filename);
    }

    LuaCEmbedResponse *response  = lua.response.send_raw_string((char*)content,size);
    free(content);
    return response;
}

LuaCEmbedResponse *write_file(LuaCEmbedTable *self,LuaCEmbed *args){
    char *filename = lua.args.get_str(args,0);
    char *content = lua.args.get_str(args,1);
    if(lua.has_errors(args)){
        char *erro_msg = lua.get_error_message(args);
        return lua.response.send_error(erro_msg);
    }
    dtw.write_string_file_content(filename,content);
    return NULL;
}

LuaCEmbedResponse *list_dirs(LuaCEmbedTable *self,LuaCEmbed *args){
    char *path = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *erro_msg = lua.get_error_message(args);
        return lua.response.send_error(erro_msg);
    }
    if(dtw.entity_type(path) != DTW_FOLDER_TYPE){
        return lua.response.send_error("not a folder");
    }
    LuaCEmbedTable *litage_table = lua.tables.new_anonymous_table(args);
    DtwStringArray *folders = dtw.list_dirs(path,true);
    long size =folders->size;
    for(int i = 0; i < size;i++){
        char *current = folders->strings[i];
        lua.tables.append_string(litage_table,current);
    }
    dtw.string_array.free(folders);
    LuaCEmbedTable *final_response = lua.tables.new_anonymous_table(args);
    lua.tables.append_table(final_response,litage_table);
    lua.tables.append_long(final_response,size);
    return lua.response.send_multi_return(final_response);
}
LuaCEmbedResponse *is_file(LuaCEmbedTable *self,LuaCEmbed *args){

}