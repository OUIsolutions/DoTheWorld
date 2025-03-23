

typedef struct {
    DtwTransaction  *transaction;
    DtwRandonizer  *randonizer;
    DtwLocker *locker;
    bool schema_unsafe;
    int error_code;
    char *error_path;
    char *error_message;
    DtwEncriptionInterface *encryption_interface;
    short encryption_mode;


}privateDtwResourceRootProps;
