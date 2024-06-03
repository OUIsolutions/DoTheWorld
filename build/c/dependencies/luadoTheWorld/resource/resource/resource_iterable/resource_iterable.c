
LuaCEmbedResponse * resource_list(LuaCEmbedTable  *self,LuaCEmbed *args) {
    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResourceArray  *elements = dtw.resource.sub_resources(resource);
    LuaCEmbedTable *response = lua.tables.new_anonymous_table(args);
    for(int i = 0; i < elements->size; i++) {
        DtwResource*current = elements->resources[i];
        LuaCEmbedTable  *sub = raw_create_resource(args,current);
        lua.tables.append_table(response,sub);
    }
    return lua.response.send_table(response);
}


LuaCEmbedResponse * resource_foreach(LuaCEmbedTable  *self,LuaCEmbed *args) {


    DtwResource  *resource = (DtwResource*)lua.tables.get_long_prop(self,RESOURCE_POINTER);
    DtwResourceArray  *elements = dtw.resource.sub_resources(resource);

    for(int i =0; i < elements->size; i++) {
        DtwResource *current = elements->resources[i];
        LuaCEmbedTable  *sub = raw_create_resource(args,current);
        LuaCEmbedTable *args_to_callback = lua.tables.new_anonymous_table(args);
        lua.tables.append_table(args_to_callback,sub);
        lua.args.run_lambda(args,0,args_to_callback,0);

    }
    return lua.response.send_table(self);

}