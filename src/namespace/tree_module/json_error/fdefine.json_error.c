//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.dep_define.h"
//silver_chain_scope_end



DtwJsonTreeErrorModule newDtwJsonTreeErrorModule(){
    DtwJsonTreeErrorModule self = {0};
    self.validate_json_tree_by_cJSON= DtwJsonTreeError_validate_json_tree_by_cJSON;
    self.validate_json_tree_by_content = DtwJsonTreeError_validate_json_tree_by_content;
    self.represent =DtwJsonTreeError_represent;
    self.free = DtwJsonTreeError_free;
    return self;
}
