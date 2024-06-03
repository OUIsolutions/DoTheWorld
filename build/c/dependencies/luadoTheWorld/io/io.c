

LuaCEmbedResponse  * load_file(LuaCEmbed *args){
    char *filename = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }

    long  size;
    bool is_binary;
    unsigned  char *content = dtw.load_any_content(filename,&size,&is_binary);
    if(!content){
        if(dtw.entity_type(filename) == DTW_FILE_TYPE){
             return lua.response.send_str("");
        }
        return NULL;
    }
    if(!is_binary){

        LuaCEmbedResponse  * response = lua.response.send_str((const char*)content);
        free(content);
        return response;
    }

    LuaCEmbedResponse  *response  = lua.response.send_raw_string((char*)content,size);
    free(content);
    return  response;
}

LuaCEmbedResponse  * write_file(LuaCEmbed *args){
    char *filename = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    bool writed = false;
    long total_args = lua.args.size(args);
    if(total_args == 0){
        writed  = dtw.write_string_file_content(filename,"");
        return lua.response.send_bool(writed);
    }

    Writeble  write_obj = create_writeble(args,1);
    if(write_obj.error){
        return write_obj.error;
    }
    writed = dtw.write_any_content(filename,write_obj.content,write_obj.size);
    Writeble_free(&write_obj);
    return  lua.response.send_bool(writed);


}
LuaCEmbedResponse  * is_dir(LuaCEmbed *args){
    char *source = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    int type = dtw.entity_type(source);
    return lua.response.send_bool(type == DTW_FOLDER_TYPE);
}

LuaCEmbedResponse  * exist(LuaCEmbed *args){
    char *source = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    int type = dtw.entity_type(source);
    return lua.response.send_bool(type != DTW_NOT_FOUND);
}

LuaCEmbedResponse  * is_byte(LuaCEmbed *args){

    if(lua.args.get_type(args,0) != lua.types.STRING){
        return lua.response.send_bool(false);
    }
    long size;
    unsigned  char *value =(unsigned  char *)lua.args.get_raw_str(args,&size,0);
    for(int i = 0; i < size; i++){
        unsigned  char current = value[i];
        if(current == 0){
            return lua.response.send_bool(true);
        }
    }

    return lua.response.send_bool(false);

}

LuaCEmbedResponse  * is_file(LuaCEmbed *args){
    char *source = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    int type = dtw.entity_type(source);
    return lua.response.send_bool(type == DTW_FILE_TYPE);
}

LuaCEmbedResponse  * is_binary(LuaCEmbed *args){
    char *source = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    int type = dtw.complex_entity_type(source);
    return lua.response.send_bool(type == DTW_COMPLEX_BINARY);
}




LuaCEmbedResponse  * copy_any_overwriting(LuaCEmbed *args){
    char *source = lua.args.get_str(args,0);
    char *dest = lua.args.get_str(args,1);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }

    bool writed = dtw.copy_any(source,dest,DTW_NOT_MERGE);
    return lua.response.send_bool(writed);
}


LuaCEmbedResponse  * copy_any_merging(LuaCEmbed *args){
    char *source = lua.args.get_str(args,0);
    char *dest = lua.args.get_str(args,1);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }

    bool writed = dtw.copy_any(source,dest,DTW_MERGE);
    return lua.response.send_bool(writed);
}

LuaCEmbedResponse  * move_any_overwriting(LuaCEmbed *args){
    char *source = lua.args.get_str(args,0);
    char *dest = lua.args.get_str(args,1);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    bool writed = dtw.move_any(source,dest,DTW_NOT_MERGE);
    return lua.response.send_bool(writed);
}
LuaCEmbedResponse  * move_any_merging(LuaCEmbed *args){
    char *source = lua.args.get_str(args,0);
    char *dest = lua.args.get_str(args,1);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    bool writed = dtw.move_any(source,dest,DTW_MERGE);
    return lua.response.send_bool(writed);
}


LuaCEmbedResponse  * remove_any(LuaCEmbed *args){
    char *source = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    bool writed = dtw.remove_any(source);
    return lua.response.send_bool(writed);
}


