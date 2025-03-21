//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.typesm.h"
//silver_chain_scope_end




unsigned char *dtw_encrypt_any_content(unsigned char *value,long size,const char* key);

unsigned char *dtw_decript_any_content(unsigned char *encriypted,long size,const char* key);


unsigned char *dtw_encrypt_string(const char *value,const char* key);

char *dtw_decrypt_string(const char *encrypted,const char* key);

bool dtw_write_any_content_encrypting(const char *path,unsigned char *content,long size,const char* key);

bool dtw_write_string_file_content_encrypting(const char *path,const char *content,const char* key);

unsigned char *dtw_load_any_content_decrypting(const char * path,const char* key,long *size,bool *is_binary);

char *dtw_load_string_file_content_decrypting(const char * path,const char* key);
