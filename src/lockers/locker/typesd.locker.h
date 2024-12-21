
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.typesc_flock_locker.h"
//silver_chain_scope_end




typedef struct {
#ifdef __linux__
    DtwFlockLocker *locker;
#endif
#ifdef _WIN32
    DtwMultiFileLocker  *locker;
#endif

} DtwLocker;
