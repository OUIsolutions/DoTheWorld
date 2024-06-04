
bool get_table_props_or_default_bool(LuaCEmbedTable *table,const char *prop,bool default_value){
    if(table == NULL){
        return default_value;
    }
    if(LuaCEmbedTable_get_type_prop(table,prop) != LUA_CEMBED_NIL){
        return LuaCembedTable_get_bool_prop(table,prop);
    }
    return default_value;
}