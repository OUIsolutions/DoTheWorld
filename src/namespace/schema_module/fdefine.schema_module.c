
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end



DtwSchemaModule newDtwSchemaModule(){
    DtwSchemaModule  self = {0};
    self.sub_schema = DtwSchema_new_subSchema;
    self.add_primary_key = DtwSchema_add_primary_key;

    return  self;
}
