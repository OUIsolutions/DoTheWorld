
DtwSchema *private_newDtwSchema(const char *name){
    DtwSchema *self = (DtwSchema*) malloc(sizeof (DtwSchema));
    *self = (DtwSchema){0};
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

DtwSchema *DtwSchema_new_sub_schema(DtwSchema *self, const char *name){


    struct DtwSchema *child = ( DtwSchema *) private_newDtwSchema(name);
    self->sub_schemas = ( DtwSchema **)realloc(self->sub_schemas, sizeof(struct DtwSchema *) * (self->size + 1));
    self->sub_schemas[self->size] = child;
    self->size++;
    return (DtwSchema*)child;
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