
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.types.h"
//silver_chain_scope_end


typedef struct {

    int total_checks;
    int process;
    int max_wait;
    int max_lock_time;
    DtwStringArray *locked_elements;


}DtwMultiFileLocker;
