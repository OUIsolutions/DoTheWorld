
DtwSchema *private_newDtwSchema(const char *name){
    DtwSchema *self = (DtwSchema*) malloc(sizeof (DtwSchema));
    *self = (DtwSchema){0};
    self->value_name = DTW_SCHEMA_DEFAULT_VALUES_NAME;
    self->index_name = DTW_SCHEMA_DEFAULT_INDEX_NAME;
    self->sub_schemas = (struct DtwSchema **)malloc(0);
    self->name = strdup(name);
    return  self;
}


DtwSchema * privateDtwSchema_get_sub_schema(DtwSchema *self,const char *name){

    for(int i = 0; i < self->size; i++){
        DtwSchema  *current = self->sub_schemas[i];
        if(strcmp(current->name,name) == 0){
            return  current;
        }
    }
    return NULL;
}


void DtwSchema_add_primary_key(DtwSchema *self,const char *name){
    DtwStringArray_append(self->primary_keys,name);
}

void private_newDtwSchema_free(DtwSchema *self){

    for (int i = 0; i < self->size; i++) {
        private_newDtwSchema_free((DtwSchema *) self->sub_schemas[i]);
    }

    free(self->sub_schemas);
    free(self->name);
    DtwStringArray_free(self->primary_keys);
    free(self);
}