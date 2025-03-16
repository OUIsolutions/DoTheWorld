
#ifdef __linux__

typedef struct {
    const char *temp_folder;
    privateDtwFlockArray  *locked_files;
}DtwFlockLocker;
#endif
