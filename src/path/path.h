
typedef struct DtwPath {
    char *original_path_string;
    char *name;
    char *extension;
    DtwStringArray *dirs;
    DtwStringArray *garbage;


}DtwPath;
struct DtwPath * newDtwPath(const char *path);
bool  DtwPath_changed( DtwPath *self);
char *DtwPath_get_full_name( DtwPath *self);
char *DtwPath_get_name( DtwPath *self);
char *DtwPath_get_extension( DtwPath *self);
char *DtwPath_get_path( DtwPath *self);
char *DtwPath_get_dir( DtwPath *self);
long DtwPath_get_dirs_size(DtwPath *self);

void DtwPath_set_extension( DtwPath *self, const char *extension);
void DtwPath_set_name( DtwPath * self, const char * name);
void DtwPath_set_dir( DtwPath *self, const char *path);

void DtwPath_set_full_name( DtwPath * self, const char * full_name);
void DtwPath_set_path( DtwPath *self, const char *target_path);

void DtwPath_add_start_dir( DtwPath *self, const char *start_dir);
void DtwPath_add_end_dir( DtwPath *self, const char *end_dir);

void DtwPath_represent( DtwPath *self);
void DtwPath_free( DtwPath *self);


