

void DtwResource_foreach(DtwResource *self, bool(*filtrage_callback)(DtwResource *item, void *args_filter), void(*callback)(DtwResource *item, void *args), void *args, int start, int qtd);