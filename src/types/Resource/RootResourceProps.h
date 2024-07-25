#include "../unique.h"

typedef struct {
    DtwTransaction  *transaction;
    DtwRandonizer  *randonizer;
    DtwLocker *locker;
    bool is_writing_schema;
    int error_code;
    char *error_path;
    char *error_message;

}privateDtwResourceRootProps;
