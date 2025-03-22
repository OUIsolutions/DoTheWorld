//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesm.h"
//silver_chain_scope_end


DtwEncriptionInterface *newDtwEncriptionInterface_raw(void *obj,    unsigned char *(*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size), unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size), void (*free_obj)(void *obj));

unsigned char *DtwEncriptionInterface_encrypt_buffer(DtwEncriptionInterface *self, unsigned char *value,long size,long *out_size);


unsigned char *DtwEncriptionInterface_decrypt_buffer(DtwEncriptionInterface *self, unsigned char *encrypted_value,long size,long *out_size,bool *is_binary);


bool DtwEncriptionInterface_write_any_content(DtwEncriptionInterface *self,const char *file_name,void *value,long size);

bool DtwEncriptionInterface_write_string_file_content(DtwEncriptionInterface *self,const char *file_name,const char *value);

unsigned char *DtwEncriptionInterface_load_any_content(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);

char *DtwEncriptionInterface_load_string_file_content(DtwEncriptionInterface *self,const char *file_name);


void DtwEncriptionInterface_free(DtwEncriptionInterface *self);
