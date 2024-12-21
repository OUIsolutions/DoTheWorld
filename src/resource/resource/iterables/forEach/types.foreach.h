
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../imports/imports.macros.h"
//silver_chain_scope_end


typedef struct{
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    void(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
}DtwResourceForeachProps;
