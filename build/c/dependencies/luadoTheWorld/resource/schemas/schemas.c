

LuaCEmbedResponse  * add_schema_primary_keys(LuaCEmbedTable *self,LuaCEmbed *args){

    DtwSchema *schema = (DtwSchema*)lua.tables.get_long_prop(self,SCHEMA_POINTER);
    int arg_type = lua.args.get_type(args,0);
    if(arg_type == lua.types.STRING){
        char *value = lua.args.get_str(args,0);
        dtw.schema.add_primary_key(schema,value);
        return lua.response.send_table(self);
    }

    if(arg_type != lua.types.TABLE){
        return lua.response.send_error(ARGUMENT_NOT_IN_STRING_OR_STRING_ARRAY);
    }

    LuaCEmbedTable *string_array = lua.args.get_table(args,0);
    long size = lua.tables.get_size(string_array);
    for(int i = 0; i < size;i++){
        int current_type = lua.tables.get_type_by_index(string_array,i);
        if(current_type != lua.types.STRING){
            return lua.response.send_error(ARGUMENT_NOT_IN_STRING_OR_STRING_ARRAY);
        }
    }

    for(int i = 0; i < size;i++){
        char *current_value = lua.tables.get_string_by_index(string_array,i);
        dtw.schema.add_primary_key(schema,current_value);
    }
    return lua.response.send_table(self);
}

LuaCEmbedResponse  * add_sub_schema(LuaCEmbedTable *self,LuaCEmbed *args){
    char *name = lua.args.get_str(args,0);
    if(lua.has_errors(args)){
        char *message = lua.get_error_message(args);
        return lua.response.send_error(message);
    }

    DtwSchema *schema = (DtwSchema*)lua.tables.get_long_prop(self,SCHEMA_POINTER);
    DtwSchema *sub_schmea = dtw.schema.sub_schema(schema,name);
    LuaCEmbedTable *created_table = raw_create_schema(args,sub_schmea);
    return lua.response.send_table(created_table);
}

LuaCEmbedTable  * raw_create_schema(LuaCEmbed *args,DtwSchema *schema){
    LuaCEmbedTable *created= lua.tables.new_anonymous_table(args);
    lua.tables.set_long_prop(created,SCHEMA_POINTER,(long long )schema);
    lua.tables.set_method(created,ADD_PRIMARY_KEYS,add_schema_primary_keys);
    lua.tables.set_method(created,ADD_SUB_SCHEMA_METHOD,add_sub_schema);
    return created;
}

