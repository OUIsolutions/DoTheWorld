


void DtwResource_map(
DtwResource *self,
void *main_array,
void(*append)(void *main_array, void *item),
bool(*filtrage_callback)(DtwResource *item, void *args_filter), 
void *(*callback)(DtwResource *item, void *args),
void *args, 
int start,
int qtd
);


