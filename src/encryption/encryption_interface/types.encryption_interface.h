
typedef struct DtwEncriptionInterface{
    void *obj;
    unsigned char * (*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size);
   unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size);
   void (*free_obj)(void *obj);
}DtwEncriptionInterface;


