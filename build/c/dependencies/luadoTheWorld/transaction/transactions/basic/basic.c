





LuaCEmbedResponse * transaction_commit(LuaCEmbedTable *self,LuaCEmbed *args) {

    const char *path = NULL;
    if(lua.args.size(args) > 0){
        path  = lua.args.get_str(args,0);
    }
    if(lua.has_errors(args)){
        char *error_message = lua.get_error_message(args);
        return  lua.response.send_error(error_message);
    }
    DtwTransaction *t = (DtwTransaction*)lua.tables.get_long_prop(self,TRANSACTION_POINTER);
    dtw.transaction.commit(t,path);
    return  lua.response.send_table(self);
}



LuaCEmbedResponse * transaction_delete(LuaCEmbedTable *self,LuaCEmbed *args) {
    DtwTransaction *t = (DtwTransaction*)lua.tables.get_long_prop(self,TRANSACTION_POINTER);
    bool ref = lua.tables.get_bool_prop(self,IS_A_REF);
    if(!ref){
        dtw.transaction.free(t);
    }
    return  NULL;
}


void  private_transaction_add_base_methods(LuaCEmbedTable *self,DtwTransaction *transaction){
    lua.tables.set_long_prop(self,TRANSACTION_POINTER,(long long)transaction);
    lua.tables.set_method(self,WRITE_METHOD,transaction_write);
    lua.tables.set_method(self,COPY_ANY_METHOD,transaction_copy_any);
    lua.tables.set_method(self,REMOVE_ANY_METHOD,transaction_remove_any);
    lua.tables.set_method(self,MOVE_ANY_METHOD,transaction_move_any);
    lua.tables.set_method(self,COPY_ANY_METHOD,transaction_copy_any);
    lua.tables.set_method(self,COMMIT_METHOD,transaction_commit);
    lua.tables.set_method(self,DUMP_TO_JSON_FILE_METHOD,transaction_dumps_to_json_file);
    lua.tables.set_method(self,DUMP_TO_JSON_STRING,transaction_dumps_to_json_string);
    lua.tables.set_method(self,EACH_METHOD,transaction_foreach);
    lua.tables.set_method(self,MAP_METHOD,transaction_map);
    lua.tables.set_method(self,COUNT_METHOD,transaction_count);
    lua.tables.set_method(self,INDEX_METHOD,transaction_index);
    lua.tables.set_method(self,FIND_METHOD,transaction_find);
    lua.tables.set_method(self,DELETE_METHOD,transaction_delete);

    int  test = lua.tables.get_type_prop(self,DELETE_METHOD);
    printf("type %s\n",lua.convert_arg_code(test));
}


LuaCEmbedResponse * transaction_new_transaction(LuaCEmbed *args){
    LuaCEmbedTable * self = lua.tables.new_anonymous_table(args);
    lua.tables.set_bool_prop(self,IS_A_REF,false);
    DtwTransaction *transaction = dtw.transaction.newTransaction();
    lua.tables.set_long_prop(self,TRANSACTION_POINTER,(long)transaction);
    if(LuaCEmbed_has_errors(self->main_object)){
        printf("error %s\n", LuaCEmbed_get_error_message(self->main_object));
    }

    private_transaction_add_base_methods(self,transaction);
    return lua.response.send_table(self);
}
