

typedef struct DtwStream{
    int error;
    FILE  *file;
    int fd;
    cJSON *elements;
}DtwLockerStream;

DtwLockerStream * privatenewDtwLockerStream(const char *file);

void  privatenewDtwLocker_free(DtwLockerStream *self);
