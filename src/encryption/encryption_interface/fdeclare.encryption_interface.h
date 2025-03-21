

DtwEncriptionInterface *newDtwEncriptionInterface_raw(void *obj,    unsigned char *(*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size), unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size), void (*free_obj)(void *obj));

unsigned char *DtwEncriptionInterface_encrypt_buffer(DtwEncriptionInterface *self, unsigned char *value,long size,long *out_size);

char *DtwEncriptionInterface_encrypt_buffer_b64(DtwEncriptionInterface *self, unsigned char *value,long size);


unsigned char *DtwEncriptionInterface_decrypt_buffer(DtwEncriptionInterface *self, unsigned char *encrypted_value,long size,long *out_size,bool *is_binary);

unsigned char *DtwEncriptionInterface_decrypt_buffer_b64(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary);

bool DtwEncriptionInterface_write_any_content(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);


bool DtwEncriptionInterface_write_any_content_b64(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);


bool DtwEncriptionInterface_write_string_file_content(DtwEncriptionInterface *self,const char *file_name,const char *value);

bool DtwEncriptionInterface_write_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name,const char *value);

unsigned char *DtwEncriptionInterface_load_any_content(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);

unsigned char *DtwEncriptionInterface_load_any_content_b64(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);

char *DtwEncriptionInterface_load_string_file_content(DtwEncriptionInterface *self,const char *file_name);

char *DtwEncriptionInterface_load_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name);


void DtwEncriptionInterface_free(DtwEncriptionInterface *self);
