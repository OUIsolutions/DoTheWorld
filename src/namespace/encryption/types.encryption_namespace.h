

typedef struct DtwEncryptionNamespace{
//initializer
DtwEncriptionInterface *(*newInterface_raw)(void *obj, unsigned char *(*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size), unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size), void (*free_obj)(void *obj));
DtwEncriptionInterface *(*newAES_ECB_EncryptionInterface)(const uint8_t* key,int key_size);
DtwEncriptionInterface *(*newAES_ECB_EncryptionInterface_str)(const char* key);
DtwEncriptionInterface *(*newAES_Custom_CBC_v1_interface)(const char *key);
DtwEncriptionInterface *(*newAES_CBC_EncryptionInterface)(const uint8_t* key,int key_size,const uint8_t *iv, int iv_size);
DtwEncriptionInterface *(*newAES_CBC_EncryptionInterface_str)(const char* key,const char *iv);


//basic
unsigned char *(*encrypt_buffer)(DtwEncriptionInterface *self, unsigned char *value,long size,long *out_size);
unsigned char *(*decrypt_buffer)(DtwEncriptionInterface *self, unsigned char *encrypted_value,long size,long *out_size,bool *is_binary);
void (*free)(DtwEncriptionInterface *self);

//basic io
bool (*write_any_content)(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);
bool (*write_string_file_content)(DtwEncriptionInterface *self,const char *file_name,const char *value);
unsigned char *(*load_any_content)(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);
char *(*load_string_file_content)(DtwEncriptionInterface *self,const char *file_name);



//hex
char *(*encrypt_buffer_hex)(DtwEncriptionInterface *self, unsigned char *value,long size);
unsigned char *(*decrypt_buffer_hex)(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary);
bool (*write_any_content_hex)(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);
bool (*write_string_file_content_hex)(DtwEncriptionInterface *self,const char *file_name,const char *value);
unsigned char *(*load_any_content_hex)(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);
char *(*load_string_file_content_hex)(DtwEncriptionInterface *self,const char *file_name);


///b64
char *(*encrypt_buffer_b64)(DtwEncriptionInterface *self, unsigned char *value,long size);
unsigned char *(*decrypt_buffer_b64)(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary);
bool (*write_any_content_b64)(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);
bool (*write_string_file_content_b64)(DtwEncriptionInterface *self,const char *file_name,const char *value);
unsigned char *(*load_any_content_b64)(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);
char *(*load_string_file_content_b64)(DtwEncriptionInterface *self,const char *file_name);


}DtwEncryptionNamespace;