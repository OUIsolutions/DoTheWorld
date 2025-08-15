//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.fdeclare.h"
//silver_chain_scope_end





char *DtwEncriptionInterface_encrypt_buffer_hex(DtwEncriptionInterface *self, unsigned char *value,long size){
    
    long encrypted_size;
    unsigned char *encrypted = DtwEncriptionInterface_encrypt_buffer(self,value,size,&encrypted_size);
    if(encrypted == NULL){
        return NULL;
    }
    char *hex = dtw_convert_binary_to_hex(encrypted,encrypted_size);
    free(encrypted);

    return hex;
}



unsigned char *DtwEncriptionInterface_decrypt_buffer_hex(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary){
    long hex_size;
    unsigned char *binary = dtw_convert_hex_to_binary(encrypted_value,&hex_size);
    unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer(self,binary,hex_size,out_size,is_binary);
    free(binary);
    return decrypted;
}


bool DtwEncriptionInterface_write_any_content_hex(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size){

    char *data = DtwEncriptionInterface_encrypt_buffer_hex(self,value,size);
    if(data == NULL){
        return false;
    }
    bool result = dtw_write_string_file_content(file_name,data);
    free(data);
    return result;
}

bool DtwEncriptionInterface_write_string_file_content_hex(DtwEncriptionInterface *self,const char *file_name,const char *value){
    return DtwEncriptionInterface_write_any_content_hex(self,file_name,(unsigned char *)value,strlen(value));
}

unsigned char *DtwEncriptionInterface_load_any_content_hex(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary){
    char *data = dtw_load_string_file_content(file_name);
    if(data == NULL){
        *is_binary = false;
        *out_size = 0;
        return NULL;
    }

    unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer_hex(self,data,out_size,is_binary);
    free(data);
    return decrypted;
}

char *DtwEncriptionInterface_load_string_file_content_hex(DtwEncriptionInterface *self,const char *file_name){
    long size;
    bool is_binary;
    unsigned char *decrypted = DtwEncriptionInterface_load_any_content_hex(self,file_name,&size,&is_binary);
    if(is_binary){
        free(decrypted);
        return NULL;
    }
    return (char *)decrypted;
}

