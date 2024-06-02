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
    char *content = dtw.load_string_file_content(filename);
    if(content == NULL){
        return lua.response.send_error("file %s not found",filename);
    }
    LuaCEmbedResponse *response  = lua.response.send_str(content);
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