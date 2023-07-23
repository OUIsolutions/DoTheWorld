

enum {
    PRIVATE_DTW_ACTION_WRITE_ANY,
    PRIVATE_DTW_ACTION_MOVE_ANY,
    PRIVATE_DTW_ACTION_COPY_ANY,
    PRIVATE_DTW_ACTION_DELETE_ANY
};


typedef struct DtwActionTransaction{
    short action_type;
    unsigned  char *content;
    long size;
    bool is_binary;

    char *source;
    char *dest;

}DtwActionTransaction;

DtwActionTransaction *newDtwActionTransaction();

DtwActionTransaction * DtwActionTransaction_write_any(unsigned  char *content,long size,bool is_binary);

DtwActionTransaction * DtwActionTransaction_move_any(unsigned  char *content,const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_copy_any(unsigned  char *content,const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_delete_any(unsigned  char *content,const char *source);

void DtwActionTransaction_represent(DtwActionTransaction* self);

void DtwActionTransaction_free(DtwActionTransaction* self);
