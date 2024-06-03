LuaCEmbedResponse * resource_to_string(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    int  type = DtwResource_type(resource);
    if(type == DTW_NOT_FOUND ||type == DTW_COMPLEX_BINARY || type == DTW_FOLDER_TYPE ){
        return  lua.response.send_str(resource->path);
    }

    char *value = dtw.resource.get_string(resource);

    return lua.response.send_str(value);
}


LuaCEmbedResponse * resource_to_number(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    double value = dtw.resource.get_double(resource);
    if(dtw.resource.error(resource)){
        char *error_message = dtw.resource.get_error_message(resource);
        LuaCEmbedResponse *response = lua.response.send_error(error_message);
        dtw.resource.clear_errors(resource);
        return response;
    }
    return lua.response.send_double(value);
}

LuaCEmbedResponse * resource_value(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    int type = dtw.resource.type(resource);

    if(type == DTW_FOLDER_TYPE || type == DTW_NOT_FOUND){
        return NULL;
    }

    if(type == DTW_COMPLEX_DOUBLE_TYPE || type == DTW_COMPLEX_LONG_TYPE){
        double value = dtw.resource.get_double(resource);
        return lua.response.send_double(value);
    }

    if(type == DTW_COMPLEX_BOOL_TYPE){
        bool value= dtw.resource.get_bool(resource);
        return lua.response.send_bool(value);
    }

    if(type == DTW_COMPLEX_BINARY || type == DTW_COMPLEX_STRING_TYPE){
        long size;
        bool is_binary;
        unsigned  char *content =  dtw.resource.get_any(resource,&size,&is_binary);
        return lua.response.send_raw_string_reference((char*)content,size);
    }

    return NULL;
}

LuaCEmbedResponse * resource_value_from_sub_resource(LuaCEmbedTable  *self,LuaCEmbed *args){
    char *src = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }

    DtwResource  *master = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResource *sub = dtw.resource.sub_resource(master,src);

    int type = dtw.resource.type(sub);

    if(type == DTW_FOLDER_TYPE || type == DTW_NOT_FOUND){
        return NULL;
    }
    if(type == DTW_COMPLEX_DOUBLE_TYPE || type == DTW_COMPLEX_LONG_TYPE){
        double value = dtw.resource.get_double(sub);
        return lua.response.send_double(value);
    }
    if(type == DTW_COMPLEX_STRING_TYPE){
        char *value = dtw.resource.get_string(sub);
        return lua.response.send_str(value);
    }

    if(type == DTW_COMPLEX_BOOL_TYPE){
        bool value= dtw.resource.get_bool(sub);
        return lua.response.send_bool(value);
    }

    if(type == DTW_COMPLEX_BINARY){
        long size;
        bool is_binary;
        unsigned  char *content =  dtw.resource.get_any(sub,&size,&is_binary);
        return lua.response.send_raw_string((char*)content,size);
    }
    return NULL;
}

LuaCEmbedResponse * resource_to_boolean(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    bool value = dtw.resource.get_bool(resource);
    if(dtw.resource.error(resource)){
        char *error_message = dtw.resource.get_error_message(resource);
        LuaCEmbedResponse *response = lua.response.send_error(error_message);
        dtw.resource.clear_errors(resource);
        return response;
    }
    return lua.response.send_bool(value);
}