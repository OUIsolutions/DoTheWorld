//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end




DtwDatabaseSchemaModule newDtwDatabaseSchemaModule(){
    DtwDatabaseSchemaModule  self = {0};
    self.sub_schema = DtwDtatabaseSchema_new_subSchema;
    return  self;
}
