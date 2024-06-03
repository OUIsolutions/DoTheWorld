
bool get_table_props_or_default_bool(LuaCEmbedTable *table,const char *prop,bool default_value){
    if(table == NULL){
        return default_value;
    }
    if(lua.tables.get_type_prop(table,prop) != lua.types.NILL){
        return lua.tables.get_bool_prop(table,prop);
    }
    return default_value;
}