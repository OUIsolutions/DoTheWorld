
struct DtwStringArray {
  int size;         
  int iterator;
  char **strings;       
}; // End the structure with a semicolon

struct DtwStringArray * dtw_create_string_array(){
    struct DtwStringArray *self = (struct DtwStringArray*)malloc(sizeof(struct DtwStringArray));
    self->size = 0;
    self->iterator = 0;
    self->strings = (char**)malloc(0);
    return self;
}


// Function prototypes
void dtw_add_string(struct DtwStringArray *self, char *string){
    self->size++;
    self->strings =  (char**)realloc(self->strings, self->size * sizeof(char *));
    self->strings[self->size - 1] = (char*)malloc(strlen(string) + 1);
    strcpy(self->strings[self->size - 1], string);
}

void dtw_append_string_array(struct DtwStringArray *self, struct DtwStringArray *other){
    for(int i = 0; i < other->size; i++){
        dtw_add_string(self, other->strings[i]);
    }
}


void dtw_represent_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        printf("%s\n", self->strings[i]);
    }
}
void dtw_free_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        free(self->strings[i]);
    }
    free(self->strings);

    free(self);
}
