

enum {
    PRIVATE_DTW_PATH_TYPE_DIR,
    PRIVATE_DTW_PATH_TYPE_NAME,
    PRIVATE_DTW_PATH_TYPE_EXTENSION
};

typedef struct {
    int path_type;
    int size;
    char *value;
}privateDtwPathElement;

privateDtwPathElement * newprivateDtwPathElement(const char *value,int path_type);

void privateDtwPathElement_set_value(privateDtwPathElement *self,const char *value);

void privateDtwPathElement_free(privateDtwPathElement *self);
