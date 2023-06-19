#define DTW_JSON_ERROR_CODE_OK 0
#define DTW_JSON_TYPE_ERROR 1
#define DTW_JSON_SYNTAX_ERROR 2
#define DTW_JSON_REQUIRED_KEY_ERROR 3
#define DTW_JSON_REQUIRED_VALUE_ERROR 4
#define DTW_JSON_NOT_FOUND_ERROR 5
#define DTW_ACTION_ERROR -1


typedef struct DtwJsonError {
    int code;
    int position;
    const char *menssage;
    void (*free)(struct DtwJsonError *self);
    void (*represent)(struct DtwJsonError *self);

}DtWJsonError;

struct DtwJsonError * newDtwJsonError();
struct DtwJsonError * DtwJsonError_validate_json_tree(char *content);
void DtwJsonError_represent_json_error(struct DtwJsonError *self);
void DtwJsonError_free_json_error(struct DtwJsonError *self);
