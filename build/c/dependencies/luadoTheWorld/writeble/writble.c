
bool handle_table_writble(Writeble *self,LuaCEmbed *args,int index){
    LuaCEmbedTable * bytes_or_resource = lua.args.get_table(args,index);
    if(lua.tables.get_type_prop(bytes_or_resource,DTW_TYPE) != lua.types.NUMBER){
        return false;
    }

    int type = lua.tables.get_long_prop(bytes_or_resource,DTW_TYPE);


    if(type == DTW_RESOURCE_TYPE) {
        DtwResource *resource = (DtwResource *) lua.tables.get_long_prop(bytes_or_resource, RESOURCE_POINTER);
        self->content = DtwResource_get_any(resource, &self->size, &self->is_binary);
        if (DtwResource_error(resource)) {
            char *message = DtwResource_get_error_message(resource);
            self->error = LuaCEmbed_send_error(message);
            DtwResource_clear_errors(resource);
            return false;
        }
        return true;
    }
    return false;

}
Writeble  create_writeble(LuaCEmbed *args,int index){
    Writeble self = {0};
    long total_args = lua.args.size(args);
    if(total_args == 0){
        self.error = lua.response.send_error(ARGUMENT_NOT_PROVIDED);
        return self;
    }

    int type_to_write = lua.args.get_type(args,index);
    bool writeble = false;
    if(type_to_write == lua.types.STRING){
        self.content = (unsigned  char*)lua.args.get_raw_str(args,&self.size,index);
        writeble = true;
    }

    if(type_to_write == lua.types.NUMBER){
        self.clear_content = true;
        double content = lua.args.get_double(args,index);
        double rest = content - (double)(long ) content;
        if(rest == 0){
            char formatted[20] = {0};
            sprintf(formatted,"%ld",(long)content);
            self.content = (unsigned char*)strdup(formatted);
            self.size = (long)strlen(formatted);
        }
        else{
            char formatted[20] = {0};
            sprintf(formatted,"%lf",content);
            self.content = (unsigned char*)strdup(formatted);
            self.size = (long)strlen(formatted);
        }
        writeble = true;
    }
    if(type_to_write == lua.types.BOOL){
        bool content  = lua.args.get_bool(args,index);
        const char *converted = content ? "true":"false";
        self.content = (unsigned char*)converted;
        self.size = (long)strlen(converted);
        writeble = true;
    }

    if(type_to_write == lua.types.TABLE){
        writeble = handle_table_writble(&self,args,index);
    }

    bool its_not_writible_and_no_other_errors = !writeble && !self.error;
    if(its_not_writible_and_no_other_errors){
        char *error = private_LuaCembed_format(NOT_WRITEBLE_ELEMENT,lua.convert_arg_code(type_to_write));
        self.error = lua.response.send_error(error);
        free(error);
        return self;
    }

    return self;
}
void Writeble_free(Writeble *self){
    if(self->clear_content){
        free(self->content);
    }
}