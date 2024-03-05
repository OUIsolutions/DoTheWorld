
typedef struct {

    char *filename;
    int file_descriptor;


}privateFlockLockedElement;

privateFlockLockedElement * private_new_privateFlockLockedElement(const char *filename,int file_descriptor);

void privateFlockLockedElement_free(privateFlockLockedElement *self);