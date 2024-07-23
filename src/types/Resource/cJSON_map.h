
typedef struct  {
    cJSON *(*callback)(DtwResource *item,void *args);
    void *args;
}private_DtwResource_cJSON_args;