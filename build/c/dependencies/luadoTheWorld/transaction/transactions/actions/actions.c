LuaCEmbedResponse * transaction_write(LuaCEmbedTable *self,LuaCEmbed *args){

    char *filename = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }


    Writeble  write_obj = create_writeble(args,1);
    if(write_obj.error){
        return write_obj.error;
    }
    bool is_binary = false;
    for(int i = 0; i < write_obj.size; i++){
        if(write_obj.content[i] == '\0'){
            is_binary = true;
        }
    }
    DtwTransaction *t = (DtwTransaction*)lua.tables.get_long_prop(self,TRANSACTION_POINTER);
    dtw.transaction.write_any(t,filename,write_obj.content,write_obj.size,is_binary);
    return  lua.response.send_table(self);
}


LuaCEmbedResponse * transaction_remove_any(LuaCEmbedTable *self,LuaCEmbed *args) {
    char *source = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    DtwTransaction *t = (DtwTransaction*)lua.tables.get_long_prop(self,TRANSACTION_POINTER);
    dtw.transaction.delete_any(t,source);
    return  lua.response.send_table(self);
}

LuaCEmbedResponse * transaction_copy_any(LuaCEmbedTable *self,LuaCEmbed *args) {
    char *source = lua.args.get_str(args,0);
    char *dest = lua.args.get_str(args,1);

    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    DtwTransaction *t = (DtwTransaction*)lua.tables.get_long_prop(self,TRANSACTION_POINTER);
    dtw.transaction.copy_any(t,source,dest);
    return  lua.response.send_table(self);
}

LuaCEmbedResponse * transaction_move_any(LuaCEmbedTable *self,LuaCEmbed *args) {
    char *source = lua.args.get_str(args,0);
    char *dest = lua.args.get_str(args,1);

    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    DtwTransaction *t = (DtwTransaction*)lua.tables.get_long_prop(self,TRANSACTION_POINTER);
    dtw.transaction.move_any(t,source,dest);
    return  lua.response.send_table(self);
}
