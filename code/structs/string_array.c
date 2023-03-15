
struct DtwStringArray * dtw_constructor_string_array(){
    struct DtwStringArray *self = (struct DtwStringArray*)malloc(sizeof(struct DtwStringArray));
    self->size = 0;

    self->strings = (char**)malloc(1);
    self->add_string = private_dtw_add_string;
    self->set_value = private_dtw_set_value;
    self->merge_string_array = private_dtw_merge_string_array;
    self->represent= private_dtw_represent_string_array;
    self->delete_string_array = private_dtw_delete_string_array;
    return self;
}

void private_dtw_set_value(struct DtwStringArray *self,int index,const char *value){
    if(index < self->size && index >= 0){
        int size = strlen(value);
        self->strings[index] = (char*)realloc(self->strings[index], size + 1);
        self->strings[index][size] = '\0';
        strcpy(self->strings[index], value);
    }
}
// Function prototypes
void private_dtw_add_string(struct DtwStringArray *self,const char *string){
    self->size++;
    self->strings =  (char**)realloc(self->strings, self->size * sizeof(char *));
    self->strings[self->size - 1] = (char*)malloc(strlen(string) + 1);
    strcpy(self->strings[self->size - 1], string);
}


void private_dtw_merge_string_array(struct DtwStringArray *self, struct DtwStringArray *other){
    for(int i = 0; i < other->size; i++){
        self->add_string(self, other->strings[i]);
    }
}


void private_dtw_represent_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        printf("%s\n", self->strings[i]);
    }
}
void private_dtw_delete_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        free(self->strings[i]);
    }
    free(self->strings);
    free(self);
}
