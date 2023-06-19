
struct DtwStringArray * newDtwStringArray(){
    struct DtwStringArray *self = (struct DtwStringArray*)malloc(sizeof(struct DtwStringArray));
    self->size = 0;

    self->strings = (char**)malloc(1);
    self->add_string = DtwStringArray_dtw_add_string;
    self->set_value = DtwStringArray_dtw_set_value;
    self->merge_string_array = DtwStringArray_dtw_merge_string_array;
    self->represent= DtwStringArray_dtw_represent_string_array;
    self->free = DtwStringArray_dtw_free_string_array;
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
void DtwStringArray_dtw_add_string(struct DtwStringArray *self, const char *string){
    self->size++;
    self->strings =  (char**)realloc(self->strings, self->size * sizeof(char *));
    self->strings[self->size - 1] = (char*)malloc(strlen(string) + 1);
    self->strings[self->size - 1][strlen(string)] = '\0';
    strcpy(self->strings[self->size - 1], string);
}


void DtwStringArray_dtw_merge_string_array(struct DtwStringArray *self, struct DtwStringArray *other){
    for(int i = 0; i < other->size; i++){
        self->add_string(self, other->strings[i]);
    }
}


void DtwStringArray_dtw_represent_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        printf("%s\n", self->strings[i]);
    }
}
void DtwStringArray_dtw_free_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        free(self->strings[i]);
    }
    free(self->strings);
    free(self);
}
