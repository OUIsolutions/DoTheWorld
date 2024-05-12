//
// Created by mateusmoutinho on 05/08/23.
//

void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size){
    if(DtwResource_error(self)){
        return ;
    }
    DtwSchema * schema = (DtwSchema*)self->mother->mother->mother->schema;

    if(schema != NULL){


        bool its_a_pk = DtwStringArray_find_position(schema->primary_keys,self->name) !=-1;

        if(its_a_pk){
            DtwResource *pk_folder = DtwResource_sub_resource(schema->index_resource,"%s",self->name);
            char *sha = dtw_generate_sha_from_any(element,size);
            DtwResource  *pk_value = DtwResource_sub_resource(pk_folder,sha);
            free(sha);
            char *mothers_name =self->mother->name;
            DtwResource_set_string(pk_value,mothers_name);
        }
    }


    if(self->allow_transaction){
        DtwTransaction_write_any(self->root_props->transaction,self->path,element,size,true);
    }
    else{
        dtw_write_any_content(self->path,element,size);
    }

    DtwResource_unload(self);
    self->loaded = true;
    self->value_size = size;
    self->value_any = (unsigned  char *) malloc(size+1);
    memcpy(self->value_any,element,size);

}


void DtwResource_set_string(DtwResource *self,const  char *element){
    if(DtwResource_error(self)){
        return ;
    }
    DtwSchema * schema = (DtwSchema*)self->mother->mother->mother->schema;

    if(schema != NULL){


        bool its_a_pk = DtwStringArray_find_position(schema->primary_keys,self->name) !=-1;

        if(its_a_pk){
            DtwResource *pk_folder = DtwResource_sub_resource(schema->index_resource,"%s",self->name);
            char *sha = dtw_generate_sha_from_string(element);
            DtwResource  *pk_value = DtwResource_sub_resource(pk_folder,sha);
            free(sha);
            char *mothers_name =self->mother->name;
            DtwResource_set_string(pk_value,mothers_name);
        }
    }


    if(self->allow_transaction){
        DtwTransaction_write_string(self->root_props->transaction,self->path,element);
    }
    else{
        dtw_write_string_file_content(self->path,element);
    }
    DtwResource_unload(self);

    self->loaded = true;

    self->value_size = (long)strlen(element);

    self->value_any = (unsigned char*)strdup(element);


}


void DtwResource_set_binary_sha(DtwResource *self, unsigned  char *value, long size){
    if(DtwResource_error(self)){
        return ;
    }
    char *generated_sha = dtw_generate_sha_from_any(value,size);
    DtwResource_set_string(self,generated_sha);
    free(generated_sha);
}

void DtwResource_set_string_sha(DtwResource *self,const char *value){
    DtwResource_set_binary_sha(self,(unsigned char*)value, (long)strlen(value));
}








void DtwResource_set_long(DtwResource *self,long element){
    if(DtwResource_error(self)){
        return ;
    }
    if(self->allow_transaction){
        DtwTransaction_write_long(self->root_props->transaction,self->path,element);
    }
    else{
        dtw_write_long_file_content(self->path,element);
    }
    DtwResource_unload(self);
    self->loaded = true;
    char result[20] ={0};
    sprintf(result,"%ld",element);
    self->value_any = (unsigned char *)strdup(result);

}

void DtwResource_set_double(DtwResource *self,double element){
    if(DtwResource_error(self)){
        return ;
    }
    if(self->allow_transaction){
        DtwTransaction_write_double(self->root_props->transaction,self->path,element);
    }
    else{
        dtw_write_double_file_content(self->path,element);
    }
    DtwResource_unload(self);
    self->loaded = true;
    char result[20] ={0};
    sprintf(result,"%lf",element);
    self->value_any = (unsigned char *)strdup(result);


}

void DtwResource_set_bool( DtwResource *self,bool element){
    if(DtwResource_error(self)){
        return ;
    }

    if(self->allow_transaction){
        DtwTransaction_write_bool(self->root_props->transaction,self->path,element);
    }
    else{
        dtw_write_bool_file_content(self->path,element);
    }

    DtwResource_unload(self);
    self->loaded = true;
    if(element){
        self->value_any = (unsigned char*)strdup("true");
    }
    else{
        self->value_any = (unsigned char*)strdup("false");

    }

}
