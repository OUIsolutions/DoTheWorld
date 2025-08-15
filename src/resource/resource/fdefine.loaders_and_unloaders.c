//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dep_define.h"
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

    if(self->root_props->encryption_interface){
        self->value_any = private_DtwEncriptionInterface_load_any_content_custom_mode(self->root_props->encryption_interface,self->path,&self->value_size,&self->is_binary,self->root_props->encryption_mode);
    }
    else{
        self->value_any = dtw_load_any_content(self->path,&self->value_size,&self->is_binary);
    }
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
