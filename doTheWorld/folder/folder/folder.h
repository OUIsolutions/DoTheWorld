

typedef struct DtwFolder{

    bool first_object;
    char *path;
    int error;

    DtwRandonizer  *randonizer;
    DtwGarbage  *garbage_array;

    unsigned char *(*get_binary_file)(struct DtwFolder *self, const char *name, long *size, DtwFolderProps *props);
    void (*set_binary_file)(struct DtwFolder *self, const char *name, unsigned  char *value, long size);


    char *(*get_string_file)(struct DtwFolder *self, const char *name, DtwFolderProps *props);
    void (*set_string_file)(struct DtwFolder *self, const char *name, const char *value);


    long (*get_long_file)(struct DtwFolder *self, const char *name);
    void (*set_long_file)(struct DtwFolder *self, const char *name, long value);


    double (*get_double_file)(struct DtwFolder *self, const char *name);
    void (*set_double_file)(struct DtwFolder *self, const char *name, double value);

    struct DtwFolder *(*sub_folder)(struct DtwFolder *self, const char*name, DtwFolderProps *props);

    int (*type_of)(struct DtwFolder *self, const char*name);
    char *(*inspect_type)(struct DtwFolder *self, int type);


    DtwStringArray  * (*list_all)(struct DtwFolder *self, DtwFolderProps *props);
    long (*size)(struct DtwFolder *self);

    void(*destroy_any)(struct DtwFolder *self, const char *name);
    void (*free)(struct DtwFolder *self);


}DtwFolder;

DtwFolder * private_newDtwFolder_raw();

DtwFolder * newDtwFolder(const char *path);

char * private_DtwFolder_create_path(struct DtwFolder *self, const char *name);


unsigned char * DtwFolder_get_binary_file(struct DtwFolder *self, const char *name, long *size, DtwFolderProps *props);
void DtwFolder_set_binary_file(struct DtwFolder *self, const char *name, unsigned  char *value, long size);



char * DtwFolder_get_string_file(struct DtwFolder *self, const char *name, DtwFolderProps *props);
void DtwFolder_set_string_file(struct DtwFolder *self, const char *name, const char *value);



long DtwFolder_get_long_file(struct DtwFolder *self, const char *name);
void DtwFolder_set_long_file(struct DtwFolder *self, const char *name, long value);

double DtwFolder_get_double_file(struct DtwFolder *self, const char *name);
void DtwFolder_set_double_file(struct DtwFolder *self, const char *name, double value);


void DtwFolder_destroy_any(struct DtwFolder *self, const char *name);
DtwStringArray  * DtwFolder_list_all(struct DtwFolder *self, DtwFolderProps *props);

DtwFolder * DtwFolder_sub_folder(struct DtwFolder *self, const char*name, DtwFolderProps *props);

long DtwFolder_size(struct DtwFolder *self);

int DtwFolder_type_of(struct DtwFolder *self, const char*name);
char *DtwFolder_inspect_type(struct DtwFolder *self, int type);

void DtwFolder_free(struct DtwFolder *self);