

void DtwResource_unload(DtwResource *self){
    if(private_DtwResource_ensure_no_errors(self)){
        return ;
    }
    if(self->loaded == false){
        return;
    }
    if(self->value_any){
        free(self->value_any);
    }

    self->value_any = NULL;
    self->is_binary = false;
    self->value_size = 0;
}

void DtwResource_load(DtwResource *self){
    if(private_DtwResource_ensure_no_errors(self)){
        return ;
    }
    DtwResource_unload(self);
    self->value_any = dtw_load_any_content(self->path,&self->value_size,&self->is_binary);
    //means its a empty string
    if(dtw_entity_type(self->path) == DTW_FILE_TYPE  && self->value_size ==0 ){
        self->value_any = (unsigned char*)strdup("");
    }
    self->loaded = true;

}
void DtwResource_load_if_not_loaded(DtwResource *self){
    if(private_DtwResource_ensure_no_errors(self)){
        return ;
    }
    if(self->loaded == false){
        DtwResource_load(self);
    }
}

