

typedef struct DtwStream{
    int error;
    FILE  *file;
    int fd;
    cJSON *elements;
}DtwLockerStream;

DtwLockerStream * privatenewDtwLockerStream(const char *file);

void  privatenewDtwLockerStream_free(DtwLockerStream *self);
