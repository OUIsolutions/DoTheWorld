

struct DtwPath {
    char *full_path;
    char *path;
    char *full_name;
    char *name;
    char *extension;
};



void dtw_create_path(struct DtwPath *self, const char *path) {
    self->full_path = (char *)malloc(0);
}

