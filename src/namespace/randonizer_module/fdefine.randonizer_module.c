//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end




DtwRandonizerModule newDtwRandonizerModule(){
    DtwRandonizerModule self = {0};
    self.newRandonizer = newDtwRandonizer;
    self.generate_num = DtwRandonizer_generate_num;
    self.generate_token =DtwRandonizer_generate_token;
    self.free = DtwRandonizer_free;
    return self;
}
