//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesc_flock_locker.h"
//silver_chain_scope_end





typedef struct {
#if defined(__linux__) || defined(__APPLE__)
    DtwFlockLocker *locker;
#endif
#ifdef _WIN32
    DtwMultiFileLocker  *locker;
#endif

} DtwLocker;
