
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end




DtwJsonTreeError * newDtwJsonError();

DtwJsonTreeError * DtwJsonTreeError_validate_json_tree_by_cJSON(cJSON *json_tree);

DtwJsonTreeError * DtwJsonTreeError_validate_json_tree_by_content(const char *content);

void DtwJsonTreeError_represent(struct DtwJsonTreeError *self);

void DtwJsonTreeError_free(struct DtwJsonTreeError *self);
