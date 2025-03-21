


unsigned char *dtw_aes_encrypt_any_content(unsigned char *value,long size,const char* key);

unsigned char *dtw_aes_decript_any_content(unsigned char *value,long size,const char* key);

unsigned char *dtw_aes_encrypt_string(const char *value,const char* key);

char *dtw_aes_decript_string(const char *value,const char* key);


bool dtw_write_aes_encrypted_any_content(const char *path,unsigned char *content,long size,const char* key);

bool dtw_write_aes_encrypted_string(const char *path,const char *content,const char* key);


unsigned char *dtw_load_aes_encrypted_content(const char * path,const char* key,long *size,bool *is_binary);

char *dtw_load_aes_encrypted_string(const char * path,const char* key);
