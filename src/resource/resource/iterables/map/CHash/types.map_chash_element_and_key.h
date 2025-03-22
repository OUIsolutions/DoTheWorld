


#ifdef DTW_ALLOW_CHASH


typedef  struct{
    char *key;
    CHash *element;
    bool free_key;
}privateDtw_CHash_element_and_key;

#endif
