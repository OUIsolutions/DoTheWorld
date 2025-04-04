

typedef  struct{
    char *(*key_provider_callback)(DtwResource *item,void *args);
    bool free_key;
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    cJSON *(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
} DtwResourcecJSONObjectMapProps;
