//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesd.h"
//silver_chain_scope_end


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
    bool encryption_owner;

}privateDtwResourceRootProps;
