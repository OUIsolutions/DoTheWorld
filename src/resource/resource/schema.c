
bool private_dtw_resource_its_a_pk(DtwResource *self){
    if(self->schema_type != PRIVATE_DTW_SCHEMA_ELEMENT_PROP){
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
    if(self->schema_type != PRIVATE_DTW_SCHEMA_ROOT){
        private_DtwResource_raise_error(
                self,
                DTW_RESOURCE_IMPOSSIBLE_TO_ADD_SUB_RESOURCE_INSIDE_SCHEMA_STRUCT,
                "only root schema can generate insertions",
                self->name
        );
        return NULL;
    }


    DtwResource *values = DtwResource_sub_resource(self,DTW_SCHEMA_VALUES_NAME);
    DtwResource  *created = DtwResource_sub_resource_random(values,NULL);

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
    self->schema_type = PRIVATE_DTW_SCHEMA_ROOT;
    self->attached_schema = private_newDtwSchema(name);
    DtwResource *values = DtwResource_sub_resource(self,DTW_SCHEMA_VALUES_NAME);
    values->schema_type = PRIVATE_DTW_SCHEMA_VALUE;
    DtwResource *index = DtwResource_sub_resource(self,DTW_SCHEMA_INDEX_NAME);
    index->schema_type = PRIVATE_DTW_SCHEMA_INDEX;

    free(name);
    self->its_the_schema_owner = true;

    self->root_props->is_writing_schema = false;

    return self->attached_schema;
}
