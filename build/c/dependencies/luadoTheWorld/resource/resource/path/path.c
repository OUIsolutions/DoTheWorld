

LuaCEmbedResponse * resource_get_path(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    return lua.response.send_str(resource->path);
}

LuaCEmbedResponse * resource_get_dir(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);

    DtwPath *path = dtw.path.newPath(resource->path);
    char *dir = dtw.path.get_dir(path);
    if(!dir){
        dtw.path.free(path);
        return NULL;
    }
    LuaCEmbedResponse *response = lua.response.send_str(dir);
    dtw.path.free(path);
    return response;
}
LuaCEmbedResponse * resource_get_name_without_extension(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);

    DtwPath *path = dtw.path.newPath(resource->path);
    char *name = dtw.path.get_name(path);
    if(!name){
        dtw.path.free(path);
        return NULL;
    }
    LuaCEmbedResponse *response = lua.response.send_str(name);
    dtw.path.free(path);
    return response;
}

LuaCEmbedResponse * resource_get_name(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    return lua.response.send_str(resource->name);
}

LuaCEmbedResponse * resource_get_extension(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);

    DtwPath *path = dtw.path.newPath(resource->path);
    char *extension = dtw.path.get_extension(path);
    if(!extension){
        dtw.path.free(path);
        return NULL;
    }
    LuaCEmbedResponse *response = lua.response.send_str(extension);
    dtw.path.free(path);
    return response;
}

LuaCEmbedResponse * resource_set_extension(LuaCEmbedTable  *self,LuaCEmbed *args){
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);

    char *extension = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    DtwPath *path = dtw.path.newPath(resource->path);
    dtw.path.set_extension(path,extension);
    DtwResource_rename(resource,dtw.path.get_full_name(path));
    dtw.path.free(path);
    return  lua.response.send_table(self);
}