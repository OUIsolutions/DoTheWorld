

#include "../unique.declaration_requirements.h"
DtwResourcecJSONArrayMapProps DtwResource_create_cJSONArrayMapProps(cJSON *(*callback)(DtwResource *item, void *args));

cJSON *DtwResource_map_cJSONArray(DtwResource *self,DtwResourcecJSONArrayMapProps props);

cJSON *DtwResource_schema_map_cJSONArray(DtwResource *self,DtwResourcecJSONArrayMapProps props);

void  *private_dtw_cJSONArray_callback(DtwResource *item,void *args);

bool private_dtw_cJSONArray_filtrage(DtwResource *item,void *args);

int private_dtw_cJSONArray_ordenation(DtwResource *item1,DtwResource *item2,void *args);

void privateDtwResource_add_to_item_to_cJSONArray_array(void* array, void *item);
