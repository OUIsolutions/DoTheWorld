
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.typesc.h"
//silver_chain_scope_end
#ifdef __linux__

typedef struct {
    const char *temp_folder;
    privateDtwFlockArray  *locked_files;
}DtwFlockLocker;
#endif
