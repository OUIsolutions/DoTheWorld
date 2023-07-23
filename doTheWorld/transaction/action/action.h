

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

