
typedef struct DtwTransaction{

    DtwActionTransaction  **actions;
    long size;

    void (*append_action)(struct DtwTransaction *self,struct DtwActionTransaction  *action);
    void (*write_any)(struct DtwTransaction *self,const char *path,unsigned char *content, long size,bool is_binary);
    void (*write_string)(struct DtwTransaction *self,const char *path,const char *content);
    void (*move_any)(struct DtwTransaction *self,const char *source,const char *dest);
    void (*copy_any)(struct DtwTransaction *self,const char *source,const char *dest);
    void (*delete_any)(struct DtwTransaction *self,const char *source);

    cJSON *(*dumps_transaction_to_json)(struct DtwTransaction *self);
    void (*dumps_transaction_to_json_file)(struct DtwTransaction *self,const char *filename);

    void (*commit)(struct DtwTransaction *self,const char *source);
    void (*represent)(struct DtwTransaction *self);
    void (*free)(struct DtwTransaction *self);

}DtwTransaction;

DtwTransaction * newDtwTransaction();

DtwTransaction * newDtwTransaction_from_json(cJSON *json_entry);

DtwJsonTransactionError * dtw_validate_json_transaction(cJSON *json_entry);

DtwJsonTransactionError * dtw_validate_json_transaction_file(const char *filename);


DtwTransaction * newDtwTransaction_from_json_file(const char *filename);


void DtwTransaction_append_action(struct DtwTransaction *self,struct DtwActionTransaction  *action);

void DtwTransaction_write_any(struct DtwTransaction *self,const char *path,unsigned char *content, long size,bool is_binary);

void DtwTransaction_write_string(struct DtwTransaction *self,const char *path,const char *content);

void DtwTransaction_move_any(struct DtwTransaction *self,const char *source,const char *dest);

void DtwTransaction_copy_any(struct DtwTransaction *self,const char *source,const char *dest);

void DtwTransaction_delete_any(struct DtwTransaction *self,const char *source);

cJSON * DtwTransaction_dumps_to_json(struct DtwTransaction *self);

void DtwTransaction_dumps_to_json_file(struct DtwTransaction *self,const char *filename);

void DtwTransaction_commit(struct DtwTransaction *self,const char *path);

void DtwTransaction_represent(struct DtwTransaction *self);


void DtwTransaction_free(struct DtwTransaction *self);
