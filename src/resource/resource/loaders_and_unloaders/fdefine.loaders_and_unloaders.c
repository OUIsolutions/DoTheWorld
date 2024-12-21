
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.fdeclare.h"
//silver_chain_scope_end



void DtwResource_unload(DtwResource *self){
    if(DtwResource_error(self)){
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
    if(DtwResource_error(self)){
        return ;
    }
    DtwResource_unload(self);
    self->value_any = dtw_load_any_content(self->path,&self->value_size,&self->is_binary);

    self->loaded = true;

}
void DtwResource_load_if_not_loaded(DtwResource *self){
    if(DtwResource_error(self)){
        return ;
    }
    if(self->loaded == false){
        DtwResource_load(self);
    }
}
