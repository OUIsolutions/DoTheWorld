//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end




DtwSchemaModule newDtwSchemaModule(){
    DtwSchemaModule  self = {0};
    self.sub_schema = DtwSchema_new_subSchema;
    self.add_primary_key = DtwSchema_add_primary_key;

    return  self;
}
