//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end



DtwStringArrayModule newDtwStringArrayModule(){
    DtwStringArrayModule self = {0};
    self.newStringArray = newDtwStringArray;
    self.set_value = DtwStringArray_set_value;
    self.append = DtwStringArray_append;
    self.pop = DtwStringArray_pop;
    self.merge = DtwStringArray_merge;
    self.represent = DtwStringArray_represent;
    self.find_position = DtwStringArray_find_position;
    self.sort = DtwStringArray_sort;
    self.free =DtwStringArray_free;
    return self;
}
