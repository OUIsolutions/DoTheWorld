
struct DtwStringArray * newDtwStringArray(){
    struct DtwStringArray *self = (struct DtwStringArray*)malloc(sizeof(struct DtwStringArray));
    self->size = 0;

    self->strings = (char**)malloc(1);

    self->append = DtwStringArray_dtw_append;
    self->set_value = DtwStringArray_dtw_set_value;
    self->merge_string_array = DtwStringArray_dtw_merge_string_array;
    self->represent= DtwStringArray_dtw_represent_string_array;
    self->free = DtwStringArray_dtw_free_string_array;
    self->sort =DtwStringArray_dtw_sort;
    self->find_position = DtwStringArray_dtw_find_position;
    return self;
}

int DtwStringArray_dtw_find_position(struct DtwStringArray *self, const char *string){
    for(int i = 0; i < self->size; i++){
        if(strcmp(self->strings[i], string) == 0){
            return i;
        }
    }
    return -1;
}


void DtwStringArray_dtw_set_value(struct DtwStringArray *self, int index, const char *value){
    if(index < self->size && index >= 0){
        int size = strlen(value);
        self->strings[index] = (char*)realloc(self->strings[index], size + 1);
        self->strings[index][size] = '\0';
        strcpy(self->strings[index], value);
    }
}

// Function prototypes
void DtwStringArray_dtw_append(struct DtwStringArray *self,const  char *string){

    self->strings =  (char**)realloc(self->strings, (self->size+ 1) * sizeof(char*));
    self->strings[self->size] = strdup(string);
    self->size+=1;
}


void DtwStringArray_dtw_merge_string_array(struct DtwStringArray *self, struct DtwStringArray *other){
    for(int i = 0; i < other->size; i++){
        self->append(self, other->strings[i]);
    }
}


void DtwStringArray_dtw_represent_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        printf("%s\n", self->strings[i]);
    }
}



void DtwStringArray_dtw_sort(struct DtwStringArray *self) {

    qsort(self->strings, self->size, sizeof(char*), private_dtw_string_cmp);


}


void DtwStringArray_dtw_free_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
            free(self->strings[i]);
    }

    free(self->strings);
    free(self);
}
