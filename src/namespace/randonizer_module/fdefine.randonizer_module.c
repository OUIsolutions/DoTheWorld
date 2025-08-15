//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dep_define.h"
//silver_chain_scope_end




DtwRandonizerModule newDtwRandonizerModule(){
    DtwRandonizerModule self = {0};
    self.newRandonizer = newDtwRandonizer;
    self.generate_num = DtwRandonizer_generate_num;
    self.generate_token =DtwRandonizer_generate_token;
    self.free = DtwRandonizer_free;
    return self;
}
