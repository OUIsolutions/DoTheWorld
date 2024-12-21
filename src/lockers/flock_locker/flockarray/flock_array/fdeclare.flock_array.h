
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../../imports/imports.globals.h"
//silver_chain_scope_end



#ifdef __linux__



privateDtwFlockArray * private_new_privateFlockArray();

int  privateDtwFlockArray_index_of(privateDtwFlockArray *self, const char *filename);

void privateDtwFlockArray_append(privateDtwFlockArray *self, const char *filename, int file_descriptor);

void privateDtwFlockArray_destroy_by_index(privateDtwFlockArray *self, int position);

void privateDtwFlockArray_represent(privateDtwFlockArray *self);

void privateDtwFlockArray_free(privateDtwFlockArray *self);
#endif
