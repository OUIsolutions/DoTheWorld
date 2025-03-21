//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../../../imports/imports.typesf.h"
//silver_chain_scope_end


typedef struct {
    void *main_array;
    void(*append)(void *main_array_arg, void *item);
    bool(*filtrage_callback)(DtwResource *item, void *args);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    void *(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
}DtwResourceMapProps;
