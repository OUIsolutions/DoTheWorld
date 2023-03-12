

struct DtwPath {
    char *full_path;
    char *path;
    char *full_name;
    char *name;
    char *extension;
};


void dtw_create_path(struct DtwPath *self, const char *ful_path) {
    self->full_path = (char *)malloc(0);
    self->path = (char *)malloc(0);
    self->full_name = (char *)malloc(0);
    self->name = (char *)malloc(0);
    self->extension = (char *)malloc(0);
}



