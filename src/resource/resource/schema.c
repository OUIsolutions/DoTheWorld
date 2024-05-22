
bool private_dtw_resource_its_a_pk(DtwResource *self){
    if(self->its_a_write_point == false){
        return false;
    }
    DtwResource *ancestor = self->mother->mother->mother;
    DtwSchema * schema = ancestor->attached_schema;
    return DtwStringArray_find_position(schema->primary_keys,self->name) !=-1;
}



DtwResource * DtwSchema_new_insertion(DtwResource *self){
    if(DtwResource_error(self)){
        return NULL;
    }

    DtwResource  *created = DtwResource_sub_resource_random(schema->values_resource,NULL);

    return created;
}
DtwSchema * DtwResource_newSchema(DtwResource *self, const char *format, ...){
    if(DtwResource_error(self)){
        return  NULL;
    }

    if(private_dtw_resource_its_a_primary_key(self)){
        private_DtwResource_raise_error(
                self,
                DTW_RESOURCE_PRIMARY_KEY_CANNOT_HAVE_SUB_SCHEMA,
                "primary key %s cannot have a sub old_schema",
                self->name
        );
        return NULL;
    }

    va_list args;
    va_start(args, format);
    char *name = private_dtw_format_vaarg(format,args);
    va_end(args);

    if(self->attached_schema){
        free(name);
        return self->attached_schema;
    }
    self->root_props->is_writing_schema = true;

    self->attached_schema = private_newDtwSchema(name);
    DtwResource *values = DtwResource_sub_resource(self,DTW_SCHEMA_VALUES_NAME);
    values->its_value_folder = true;
    DtwResource *index = DtwResource_sub_resource(self,DTW_SCHEMA_INDEX_NAME);
    index->its_index_folder = true;

    free(name);
    self->its_the_schema_owner = true;

    self->root_props->is_writing_schema = false;

    return self->attached_schema;
}
