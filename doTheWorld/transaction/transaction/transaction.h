
typedef struct DtwTransaction{



    void (*write_any)(struct DtwTransaction *self,const char *path,unsigned char *content, long size);
    void (*write_string)(struct DtwTransaction *self,const char *path,const char *content);
    void (*move_any)(struct DtwTransaction *self,const char *source,const char *dest);
    void (*copy_any)(struct DtwTransaction *self,const char *source,const char *dest);
    void (*delete_any)(struct DtwTransaction *self,const char *source);
    void (*free)(struct DtwTransaction *self);

}DtwTransaction;

DtwTransaction * newDtwTransaction();

void DtwTransaction_write_any(struct DtwTransaction *self,const char *path,unsigned char *content, long size);

void DtwTransaction_write_string(struct DtwTransaction *self,const char *path,const char *content);

void DtwTransaction_move_any(struct DtwTransaction *self,const char *source,const char *dest);

void DtwTransaction_copy_any(struct DtwTransaction *self,const char *source,const char *dest);

void DtwTransaction_delete_any(struct DtwTransaction *self,const char *source);

void DtwTransaction_free(struct DtwTransaction *self);
