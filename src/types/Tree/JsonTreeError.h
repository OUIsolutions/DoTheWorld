#ifndef PRIVATE_DTW_JSON_TREE_ERROR_TYPE_H
#define PRIVATE_DTW_JSON_TREE_ERROR_TYPE_H
typedef struct DtwJsonTreeError {
    int code;
    int position;
    const char *menssage;


}DtwJsonTreeError;
#endif
