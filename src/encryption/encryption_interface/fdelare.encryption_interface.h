

DtwEncriptionInterface *newDtwEncriptionInterface_raw(void *obj, int (*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size), unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size), void (*free_obj)(void *obj));

void DtwEncriptionInterface_free(DtwEncriptionInterface *self);

void DtwEncriptionInterface_write_any_content(DtwEncriptionInterface *self, char *file_name,void *value,long size);

void DtwEncriptionInterface_write_string_file_content(DtwEncriptionInterface *self, char *file_name,const char *value);

unsigned char *DtwEncriptionInterface_load_any_content(DtwEncriptionInterface *self, char *file_name,long *size);

char *DtwEncriptionInterface_load_string_file_content(DtwEncriptionInterface *self, char *file_name);
