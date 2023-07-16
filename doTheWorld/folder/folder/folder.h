

typedef struct DtwFolder{

    bool first_object;
    char *path;
    int error;

    DtwRandonizer  *randonizer;
    DtwGarbage  *garbage_array;

    unsigned char *(*get_binary)(struct DtwFolder *self, const char *name, long *size, DtwFolderProps *props);
    void (*set_binary)(struct DtwFolder *self, const char *name, unsigned  char *value, long size);


    char *(*get_string)(struct DtwFolder *self, const char *name, DtwFolderProps *props);
    void (*set_string)(struct DtwFolder *self, const char *name, const char *value);


    long (*get_long)(struct DtwFolder *self, const char *name);
    void (*set_long)(struct DtwFolder *self, const char *name, long value);


    double (*get_double)(struct DtwFolder *self, const char *name);
    void (*set_double)(struct DtwFolder *self, const char *name, double value);

    struct DtwFolder *(*sub_object)(struct DtwFolder *self, const char*name, DtwFolderProps *props);

    int (*type_of)(struct DtwFolder *self, const char*name);
    char *(*inspect_type)(struct DtwFolder *self, int type);


    DtwStringArray  * (*list_all)(struct DtwFolder *self, DtwFolderProps *props);
    long (*size)(struct DtwFolder *self);

    void(*destroy)(struct DtwFolder *self, const char *name);
    void (*free)(struct DtwFolder *self);


}DtwFolder;

DtwFolder * private_newDtwFolder_raw();

DtwFolder * newDtwFolder(const char *path);

char * private_DtwFolder_create_path(struct DtwFolder *self, const char *name);


unsigned char * DtwFolder_get_binary(struct DtwFolder *self, const char *name, long *size, DtwFolderProps *props);
void DtwFolder_set_binary(struct DtwFolder *self, const char *name, unsigned  char *value, long size);



char * DtwFolder_get_string(struct DtwFolder *self, const char *name, DtwFolderProps *props);
void DtwFolder_set_string(struct DtwFolder *self, const char *name, const char *value);



long DtwFolder_get_long(struct DtwFolder *self, const char *name);
void DtwFolder_set_long(struct DtwFolder *self, const char *name, long value);

double DtwFolder_get_double(struct DtwFolder *self, const char *name);
void DtwFolder_set_double(struct DtwFolder *self, const char *name, double value);


void DtwFolder_destroy(struct DtwFolder *self, const char *name);
DtwStringArray  * DtwFolder_list_all(struct DtwFolder *self, DtwFolderProps *props);

DtwFolder * DtwFolder_sub_object(struct DtwFolder *self, const char*name, DtwFolderProps *props);

long DtwFolder_size(struct DtwFolder *self);

int DtwFolder_type_of(struct DtwFolder *self, const char*name);
char *DtwFolder_inspect_type(struct DtwFolder *self, int type);

void DtwFolder_free(struct DtwFolder *self);