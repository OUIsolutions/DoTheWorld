//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.fdeclare.h"
//silver_chain_scope_end


#if !defined(DTW_MOCK_CJSON_DEFINE) && defined(DTW_CJSON_IMPLEMENTED)
#include "../../dependencies/cJSON.c"
#endif

#if !defined(DTW_MOCK_SHA256_DEFINE) && defined(DTW_SHA256_IMPLEMENTED)
#include "../../dependencies/sha-256.c"
#endif

#if !defined(DTW_MOCK_AES_DEFINE) && defined(DTW_AES_IMPLEMENTED)
#include "../../dependencies/aes.c"
#endif