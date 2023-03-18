#define DTW_JSON_ERROR_CODE_OK 0
#define DTW_JSON_TYPE_ERROR 1
#define DTW_JSON_SYNTAX_ERROR 2
#define DTW_JSON_REQUIRED_KEY_ERROR 3
#define DTW_JSON_REQUIRED_VALUE_ERROR 4
#define DTW_JSON_NOT_FOUND_ERROR 5

struct DtWJsonError {
    int code;
    int position;
    const char *message;
    void (*free_json_error)(struct DtWJsonError *self);

};
struct DtWJsonError * private_dtw_json_error_constructor();
struct DtWJsonError * dtw_validate_json_tree(struct DtWJsonError*self, char *content);
void private_free_json_error(struct DtWJsonError *self);