

typedef struct DtwStream{
    int error;
    FILE  *file;
    int fd;
    cJSON *elements;
}DtwLockerStream;

DtwLockerStream * privatenewDtwLockerStream(const char *file);

//void  privatenewDtwLockerStream_set_elements(DtwLockerStream *self,cJSON *elements);
int   privatenewDtwLockerStream_set_elements(const char *filename,cJSON *elements);

void  privatenewDtwLockerStream_free(DtwLockerStream *self);
