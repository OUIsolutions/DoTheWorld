#define DTW_RESOURCE_ELEMENT_IS_NULL -1;
#define DTW_RESOURCE_OK 0
#define DTW_RESOURCE_ELEMENT_NOT_EXIST 1
#define DTW_RESOURCE_ELEMENT_NOT_BOOL 2
#define DTW_RESOURCE_ELEMENT_NOT_LONG 3
#define DTW_RESOURCE_ELEMENT_NOT_DOUBLE 4
#define DTW_RESOURCE_ELEMENT_NOT_STRING 5
#define DTW_RESOURCE_PRIMARY_KEY_ALREADY_EXIST 6
#define DTW_RESOURCE_PRIMARY_KEY_CANNOT_HAVE_SUB_RESOURCE 7
#define DTW_IMPOSSIBLE_TO_RENAME_A_PRIMARY_KEY 8
#define DTW_RESOURCE_PRIMARY_KEY_CANNOT_HAVE_SUB_SCHEMA 9

typedef struct {
    DtwTransaction  *transaction;
    DtwRandonizer  *randonizer;
    DtwLocker *locker;
    int error_code;
    char *error_path;
    char *error_message;
    
}privateDtwResourceRootProps;

privateDtwResourceRootProps *private_newDtwResourceRootProps();


void privateDtwResourceRootProps_free(privateDtwResourceRootProps *self);

