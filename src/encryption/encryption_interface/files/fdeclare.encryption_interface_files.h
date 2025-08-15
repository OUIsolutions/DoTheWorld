//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.typesm.h"
//silver_chain_scope_end








bool DtwEncriptionInterface_write_any_content(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);



bool DtwEncriptionInterface_write_string_file_content(DtwEncriptionInterface *self,const char *file_name,const char *value);


unsigned char *DtwEncriptionInterface_load_any_content(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);


char *DtwEncriptionInterface_load_string_file_content(DtwEncriptionInterface *self,const char *file_name);



