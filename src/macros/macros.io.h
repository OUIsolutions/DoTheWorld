
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.consts.h"
//silver_chain_scope_end

#ifdef __linux__
#define dtw_create_dir(path) mkdir(path,0777)
#elif _WIN32
#define dtw_create_dir(path) _mkdir(path)

#endif


