


cJSON *DtwResource_map_cJSON(
DtwResource *self,
bool(*filtrage_callback)(DtwResource *item, void *args_filter),
cJSON *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd,
);

void privateDtwResource_add_to_item_to_array(void* array, void *item);


