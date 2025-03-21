//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.fdeclare.h"
//silver_chain_scope_end



DtwResourceArrayModule newDtwResourceArrayModule(){
    DtwResourceArrayModule self = {0};
    self.append = DtwResourceArray_append;
    self.represent = DtwResourceArray_represent;
    self.get_by_name = DtwResourceArray_get_by_name;
    self.free = DtwResourceArray_free;
    return self;
}
