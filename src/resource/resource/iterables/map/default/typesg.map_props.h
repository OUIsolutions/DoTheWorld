

typedef struct {
    void *main_array;
    void(*append)(void *main_array_arg, void *item);
    bool(*filtrage_callback)(DtwResource *item, void *args);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    void *(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
}DtwResourceMapProps;
