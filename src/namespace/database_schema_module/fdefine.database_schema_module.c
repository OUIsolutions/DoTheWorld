
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end



DtwDatabaseSchemaModule newDtwDatabaseSchemaModule(){
    DtwDatabaseSchemaModule  self = {0};
    self.sub_schema = DtwDtatabaseSchema_new_subSchema;
    return  self;
}
