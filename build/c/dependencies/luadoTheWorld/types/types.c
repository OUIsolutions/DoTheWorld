



LuaCEmbedResponse * ensure_table_type(LuaCEmbedTable *table,int expected_type,const char *expected_type_string){

    if(lua.tables.get_type_prop(table,DTW_TYPE) != lua.types.NUMBER){
        char formated_error[100] = {0};
        sprintf(formated_error,NOT_EXPECTED_TYPE,expected_type_string);
        return lua.response.send_error(formated_error);
    }
    long type = lua.tables.get_long_prop(table,DTW_TYPE);
    if(type !=  expected_type){
        char formated_error[100] = {0};
        sprintf(formated_error,NOT_EXPECTED_TYPE,expected_type_string);
        return lua.response.send_error(formated_error);
    }
    return NULL;
}
