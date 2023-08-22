

void DtwResource_unload(DtwResource *self){
    if(self->loaded == false){
        return;
    }
    if(self->value_any){
        free(self->value_any);
    }
    self->is_binary = false;
    self->value_size = 0;
}

void DtwResource_load(DtwResource *self){

    DtwResource_unload(self);
    self->value_any = dtw_load_any_content(self->path,&self->value_size,&self->is_binary);
    self->loaded = true;

}
void DtwResource_load_if_not_loaded(DtwResource *self){
    if(self->loaded == false){
        DtwResource_load(self);
    }
}

