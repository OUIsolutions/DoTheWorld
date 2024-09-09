
#include "../unique.definition_requirements.h"


DtwResourceArray * newDtwResourceArray(){
    DtwResourceArray *self = (DtwResourceArray*) malloc(sizeof (DtwResourceArray));
    self->resources = (DtwResource**) malloc(0);
    self->size = 0;
    return self;
}


void DtwResourceArray_append(DtwResourceArray *self, DtwResource *element){
    self->resources = (DtwResource**)realloc(self->resources,(self->size +1) * sizeof (DtwResource**));
    self->resources[self->size] = element;
    self->size+=1;
}


DtwResource* DtwResourceArray_get_by_name(DtwResourceArray *self, const char *name){
    for(int i = 0; i < self->size; i++){
        DtwResource *current = self->resources[i];
        if(strcmp(current->name,name) ==0){
            return current;
        }
    }
    return NULL;
}



void DtwResourceArray_represent(DtwResourceArray *self){
    for(int i = 0; i< self->size; i++){
        printf("----------------------------------------\n");
        DtwResource_represent(self->resources[i]);
    }
}

void DtwResourceArray_free(DtwResourceArray *self){
    for(int i = 0; i < self->size; i++){
        DtwResource_free(self->resources[i]);

    }
    free(self->resources);
    free(self);
}
