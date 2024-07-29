

#include "../unique.declaration_requirements.h"

DtwResourcecJSONObjectMapProps DtwResource_create_cJSONObjectProps(
    cJSON *(*callback)(DtwResource *item, void *args),
    char *(*key_provider_callback)(DtwResource *item,void *args)
);

cJSON *DtwResource_map_cJSONObject(DtwResource *self,DtwResourcecJSONObjectMapProps props);

cJSON *DtwResource_schema_map_cJSONObject(DtwResource *self,DtwResourcecJSONObjectMapProps props);

void  *private_dtw_cJSONArray_callback(DtwResource *item,void *args);

bool private_dtw_cJSONArray_filtrage(DtwResource *item,void *args);

int private_dtw_cJSONArray_ordenation(DtwResource *item1,DtwResource *item2,void *args);

void privateDtwResource_add_to_item_to_cJSONObject(void* object, void *item);
