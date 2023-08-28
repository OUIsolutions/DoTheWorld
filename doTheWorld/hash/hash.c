





DtwHash * newDtwHash(){
    DtwHash *self = (DtwHash*) malloc(sizeof(DtwHash));
    self->hash = dtw_generate_sha_from_string("");
}

void  DtwHash_digest_any(DtwHash *self,unsigned char *content,long size){
    if(content == NULL){
        return;
    }
    char *generated = dtw_generate_sha_from_any(content,size);
    char result[300] ={0};
    sprintf(result,"%s%s",self->hash,generated);
    free(generated);
    free(self->hash);
    self->hash = dtw_generate_sha_from_string(result);
}

void  DtwHash_digest_string(DtwHash * self, const char *content){
    DtwHash_digest_any(self,(unsigned char *)content, (long)strlen(content));
}

void  DtwHash_digest_file(DtwHash * self, const char *path){
    long size;
    unsigned  char *content = dtw_load_binary_content(path,&size);
    DtwHash_digest_any(self,content,size);
    free(content);
}

void  DtwHash_digest_entity_last_modification(DtwHash * self, const char *path){
    long last = dtw_get_entity_last_motification_in_unix(path);
    char formated[20] ={0};
    sprintf(formated,"%ld",last);
    DtwHash_digest_string(self,formated);
}

void  DtwHash_digest_string_array(DtwHash *self,DtwStringArray *element){
    DtwStringArray  *clone = DtwStringArray_clone(element);
    DtwStringArray_sort(clone);

    for(int i =0 ; i < clone->size; i++){
        DtwHash_digest_string(self,clone->strings[i]);
    }
    DtwStringArray_free(clone);
}

void  DtwHash_digest_string_array_last_modifications(DtwHash *self,DtwStringArray *element){
    DtwStringArray  *clone = DtwStringArray_clone(element);
    DtwStringArray_sort(clone);
    for(int i =0 ; i < clone->size; i++){
        DtwHash_digest_entity_last_modification(self, clone->strings[i]);
    }
    DtwStringArray_free(clone);

}

void DtwHash_digest_string_array_last_modifications_adding_name(DtwHash *self,DtwStringArray *element){
    DtwStringArray  *clone = DtwStringArray_clone(element);
    DtwStringArray_sort(clone);
    for(int i =0 ; i < clone->size; i++){
        DtwHash_digest_string(self,clone->strings[i]);
        DtwHash_digest_entity_last_modification(self, clone->strings[i]);
    }
    DtwStringArray_free(clone);
}


void DtwHash_digest_string_array_content(DtwHash *self,DtwStringArray *element){
    DtwStringArray  *clone = DtwStringArray_clone(element);
    DtwStringArray_sort(clone);
    for(int i =0 ; i < clone->size; i++){
        DtwHash_digest_file(self,clone->strings[i]);
    }
    DtwStringArray_free(clone);
}

void DtwHash_digest_string_array_content_adding_name(DtwHash *self,DtwStringArray *element){
    DtwStringArray  *clone = DtwStringArray_clone(element);
    DtwStringArray_sort(clone);
    for(int i =0; i < clone->size; i++){
        DtwHash_digest_string(self,clone->strings[i]);
        DtwHash_digest_file(self,clone->strings[i]);
    }
    DtwStringArray_free(clone);
}


void DtwHash_digest_folder_by_last_modification(DtwHash *self,const char *path){
    DtwStringArray  *folder = DtwTree_list_all_recursively(path,DTW_NOT_CONCAT_PATH);
    DtwStringArray_sort(folder);
    for(int i =0; i < folder->size; i++){
        DtwHash_digest_string(self,folder->strings[i]);
        DtwHash_digest_entity_last_modification(self, folder->strings[i]);
    }
    DtwStringArray_free(folder);
}

void DtwHash_digest_folder_by_content(DtwHash *self,const char *path){
    DtwStringArray  *folder = DtwTree_list_all_recursively(path,DTW_NOT_CONCAT_PATH);
    DtwStringArray_sort(folder);
    for(int i =0; i < folder->size; i++){
        DtwHash_digest_string(self,folder->strings[i]);
        DtwHash_digest_file(self,folder->strings[i]);
    }
    DtwStringArray_free(folder);
}

void  DtwHash_free(DtwHash *self){
    free(self->hash);
    free(self);
}