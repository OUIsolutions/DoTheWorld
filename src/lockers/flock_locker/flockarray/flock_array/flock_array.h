


typedef struct {
    privateFlockLockedElement **elements;
    int size;
}privateFlockArray;


privateFlockArray * private_new_privateFlockArray();


privateFlockLockedElement * privateFlockArray_destroy_by_index(privateFlockArray *self, int position);

int  privateFlockArray_index_of(privateFlockArray *self, const char *filename);

void privateFlockArray_append(privateFlockArray *self,const char *filename, int file_descriptor);

void privateFlockArray_represent(privateFlockArray *self);

void privateFlockArray_free(privateFlockArray *self);