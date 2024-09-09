#ifndef DTW_NOT_IMPLEMENT_CJSON
    #ifdef PRIVATE_DTW_CJSON_DEFINED_IN_DO_THE_WORLD
        #include "cJSON/cJSON.c"
        #undef true
        #define true 1
        #undef false
        #define false 0
    #endif
#endif

#ifndef DTW_NOT_IMPLEMENT_SHA256
    #ifdef PRIVATE_DTW_SHA_DEFINED_IN_DO_THE_WORLD
        #include "sha256/sha-256.c"
    #endif
#endif
