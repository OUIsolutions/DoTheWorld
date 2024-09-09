#include "../unique.all_types_less_dependencies.h"

#ifndef PRIVATE_DTW_JSON_TREE_ERROR_MODULE_TYPE_H
#define PRIVATE_DTW_JSON_TREE_ERROR_MODULE_TYPE_H
typedef struct DtwJsonTreeErrorModule{

    DtwJsonTreeError * (*validate_json_tree_by_cJSON)(cJSON *json_tree);
    DtwJsonTreeError * (*validate_json_tree_by_content)(const char *content);
    void (*free)(struct DtwJsonTreeError *self);
    void (*represent)(struct DtwJsonTreeError *self);

}DtwJsonTreeErrorModule;
#endif
