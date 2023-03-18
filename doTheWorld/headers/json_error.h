#define JSON_ERROR_CODE_OK 0
#define JSON_TYPE_ERROR 1
#define JSON_SYNTAX_ERROR 2
#define JSON_REQUIRED_KEY_ERROR 3
#define JSON_REQUIRED_VALUE_ERROR 4
#define JSON_NOT_FOUND_ERROR 5

struct JsonError {
    int code;
    int position;
    const char *message;
    void (*free)(struct JsonError *self);
};
struct JsonError * dtw_validate_json_tree(char *content);
void dtw_json_error_free(struct JsonError *self);