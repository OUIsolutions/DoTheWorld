
void private_DtwResurce_destroy_primary_key(DtwResource *self,void *vschma) {

    DtwSchema  *schema = (DtwSchema*)vschma;

    if (!DtwResource_is_file(self)) {
        return;
    }
    DtwResource *pk_index_folder = DtwResource_sub_resource(schema->index_resource, "%s", self->name);
    long size;
    bool is_binary;
    unsigned char *possible_pk_value = DtwResource_get_any(self, &size, &is_binary);
    char *pk_sha = dtw_generate_sha_from_any(possible_pk_value, size);

    DtwResource *pk_index_value = DtwResource_sub_resource(pk_index_folder, "%s", pk_sha);

    if (self->allow_transaction) {
        DtwTransaction_delete_any(self->root_props->transaction, pk_index_value->path);
    } else {
        dtw_remove_any(pk_index_value->path);
    }


}
void private_DtwResource_destroy_all_primary_keys(DtwResource *self){
    DtwSchema * schema = (DtwSchema*)self->mother->mother->schema;
    for(int i = 0; i < schema->primary_keys->size; i++){
        char *current_pk = schema->primary_keys->strings[i];
        DtwResource *son = DtwResource_sub_resource(self,"%s",current_pk);
        private_DtwResurce_destroy_primary_key(son,schema);
    }
}
void DtwResource_destroy(DtwResource *self){
    if(DtwResource_error(self)){
        return;
    }

    if(self->its_a_element_folder){
        private_DtwResource_destroy_all_primary_keys(self);
    }

    if(private_dtw_resource_its_a_primary_key(self)){
        DtwSchema * schema = (DtwSchema*)self->mother->mother->mother->schema;
        private_DtwResurce_destroy_primary_key(self,schema);
    }


    if(self->allow_transaction){
        DtwTransaction_delete_any(self->root_props->transaction,self->path);
    }
    else{
        dtw_remove_any(self->path);
    }

}

void DtwResource_destroy_sub_resource(DtwResource *self, const char *key){
    if(DtwResource_error(self)){
        return;
    }
    DtwResource *son = DtwResource_sub_resource(self, "%s",key);
    DtwResource_destroy(son);
}

