

enum {
    DTW_ACTION_WRITE,
    DTW_ACTION_MOVE,
    DTW_ACTION_COPY,
    DTW_ACTION_DELETE
};


typedef struct DtwActionTransaction{
    short action_type;
    unsigned  char *content;
    long size;
    bool is_binary;

    char *dest;
    char *source;

}DtwActionTransaction;

DtwActionTransaction *newDtwActionTransaction();

DtwActionTransaction * private_DtwActionTransaction_parse_json_object(cJSON *json_obj);


DtwActionTransaction * DtwActionTransaction_write_any(const char *source,unsigned  char *content,long size,bool is_binary);

DtwActionTransaction * DtwActionTransaction_move_any(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_copy_any(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_delete_any(const char *source);


char * DtwActionTransaction_convert_action_in_string(int action);

cJSON *  private_DtwActionTransaction_create_json_object(DtwActionTransaction* self);


void DtwActionTransaction_commit(DtwActionTransaction* self,const char *path);

void DtwActionTransaction_represent(DtwActionTransaction* self);

void DtwActionTransaction_free(DtwActionTransaction* self);
