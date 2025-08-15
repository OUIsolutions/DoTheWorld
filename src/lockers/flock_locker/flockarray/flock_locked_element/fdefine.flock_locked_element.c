//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../../imports/imports.dep_define.h"
//silver_chain_scope_end

#if defined(__linux__) || defined(__APPLE__)



privateDtwFlockLockedElement * private_new_privateDtwFlockLockedElement(const char *filename, int file_descriptor){
    privateDtwFlockLockedElement *self = (privateDtwFlockLockedElement*) malloc(sizeof (privateDtwFlockLockedElement));
    self->filename = strdup(filename);
    self->file_descriptor = file_descriptor;
    return  self;
}

void privateDtwFlockLockedElement_represent(privateDtwFlockLockedElement *self){
    printf("file: %s\n",self->filename);
    printf("if: %d\n",self->file_descriptor);

}
void privateDtwFlockLockedElement_free(privateDtwFlockLockedElement *self){
    free(self->filename);
    free(self);

}
#endif
