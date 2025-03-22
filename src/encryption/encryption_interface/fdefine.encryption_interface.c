//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end


DtwEncriptionInterface *newDtwEncriptionInterface_raw(void *obj,    unsigned char *(*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size), unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size), void (*free_obj)(void *obj)){
    DtwEncriptionInterface *self = (DtwEncriptionInterface *)malloc(sizeof(DtwEncriptionInterface));
    self->obj = obj;
    self->encrypt_buffer = encrypt_buffer;
    self->decrypt_buffer = decrypt_buffer;
    self->free_obj = free_obj;
    return self;
}

unsigned char *DtwEncriptionInterface_encrypt_buffer(DtwEncriptionInterface *self, unsigned char *value,long size,long *out_size){
    *out_size = 0;
    unsigned char *encrypted = self->encrypt_buffer(self->obj,value,size,out_size);
    encrypted[*out_size] = '\0';


    return encrypted;
}

char *DtwEncriptionInterface_encrypt_buffer_b64(DtwEncriptionInterface *self, unsigned char *value,long size){
    long encrypted_size = 0;
    unsigned char * encrypted = DtwEncriptionInterface_encrypt_buffer(self,value,size,&encrypted_size);
    if(encrypted == NULL){
        return NULL;
    }
    char *b64 = dtw_base64_encode(encrypted,encrypted_size);
    free(encrypted);
    return b64;
}


unsigned char *DtwEncriptionInterface_decrypt_buffer(DtwEncriptionInterface *self, unsigned char *encrypted_value,long size,long *out_size,bool *is_binary){
    *is_binary = false;
    *out_size = 0;
    unsigned char *content =  self->decrypt_buffer(self->obj,encrypted_value,size,out_size);
    if(content == NULL){
        return NULL;
    }
    content[*out_size] = '\0';
    for(int i= 0; i < *out_size; i++){
        if(content[i] == '\0'){
            *is_binary = true;
            break;
        }    
    }
    return content;

}

unsigned char *DtwEncriptionInterface_decrypt_buffer_b64(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary){
    
    long b64_out_size;
    unsigned char *decoded = dtw_base64_decode(encrypted_value,&b64_out_size);
    if(decoded == NULL){
        return NULL;
    }
    unsigned char * decrypted =  DtwEncriptionInterface_decrypt_buffer(self,decoded,b64_out_size,out_size,is_binary);
    free(decoded);
    return decrypted;
}


bool DtwEncriptionInterface_write_any_content(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size){
    long encrypted_size = 0;
    unsigned char * encrypted = DtwEncriptionInterface_encrypt_buffer(self,(unsigned char *)value,size,&encrypted_size);
    if(encrypted == NULL){
        return false;
    }
    printf("encrypted_size %ld\n",encrypted_size);
    bool result = dtw_write_any_content(file_name,(unsigned char *)encrypted,encrypted_size);
    free(encrypted);
    return result;
}
bool DtwEncriptionInterface_write_any_content_b64(DtwEncriptionInterface *self,const char *file_name,unsigned char *value,long size){
    char *b64 = DtwEncriptionInterface_encrypt_buffer_b64(self,(unsigned char *)value,size);
    if(b64 == NULL){
        return false;
    }
    bool result = dtw_write_any_content(file_name,(unsigned char *)b64,strlen(b64));
    free(b64);
    return result;
}


bool DtwEncriptionInterface_write_string_file_content(DtwEncriptionInterface *self,const char *file_name,const char *value){
    return DtwEncriptionInterface_write_any_content(self,file_name,(unsigned char *)value,strlen(value));
}

bool DtwEncriptionInterface_write_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name,const char *value){
    return DtwEncriptionInterface_write_any_content_b64(self,file_name,(unsigned char *)value,strlen(value));
}

unsigned char *DtwEncriptionInterface_load_any_content(DtwEncriptionInterface *self,const char *file_name,long *out_size,bool *is_binary){
    
    long raw_size;
    unsigned char *loaded = dtw_load_binary_content(file_name,&raw_size);
    if(loaded == NULL){
        return NULL;
    }
    unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer(self,loaded,raw_size,out_size,is_binary);
    free(loaded);
    return decrypted;
}

unsigned char *DtwEncriptionInterface_load_any_content_b64(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary){
    char *loaded = dtw_load_string_file_content(file_name);
    unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer_b64(self,(const char *)loaded,out_size,is_binary);
    free(loaded);
    return decrypted;
}


char *DtwEncriptionInterface_load_string_file_content(DtwEncriptionInterface *self,const char *file_name){
    bool is_binary;
    long out_size;
    unsigned char *loaded = DtwEncriptionInterface_load_any_content(self,file_name,&out_size,&is_binary);
    printf("out_size %ld\n",out_size);
    if(loaded == NULL){
        return NULL;
    }
    if(is_binary){
        free(loaded);
        return NULL;
    }
    
    return (char *)loaded;
}


char *DtwEncriptionInterface_load_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name){
    long size;
    bool is_binary;
    unsigned char *content = DtwEncriptionInterface_load_any_content_b64(self,file_name,&size,&is_binary);
    if(content == NULL){
        return NULL;
    }
    if(is_binary){
        free(content);
        return NULL;
    }
    return (char*)content;
}

void DtwEncriptionInterface_free(DtwEncriptionInterface *self){
    self->free_obj(self->obj);
    free(self);
}