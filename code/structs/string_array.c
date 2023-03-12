
struct DtwStringArray {
  int size;         
  int iterator;
  char **strings;       
  void (*add_string)(struct DtwStringArray *self, char *string);
  void (*append_string_array)(struct DtwStringArray *self, struct DtwStringArray *other);
  void (*represent)(struct DtwStringArray *self);
  void (*delete)(struct DtwStringArray *self);
}; // End the structure with a semicolon

void private_dtw_add_string(struct DtwStringArray *self, char *string);
void private_dtw_append_string_array(struct DtwStringArray *self, struct DtwStringArray *other);
void private_dtw_represent_string_array(struct DtwStringArray *self);
void private_dtw_delete_string_array(struct DtwStringArray *self);


struct DtwStringArray * dtw_constructor_string_array(){
    struct DtwStringArray *self = (struct DtwStringArray*)malloc(sizeof(struct DtwStringArray));
    self->size = 0;
    self->iterator = 0;
    self->strings = (char**)malloc(0);
    self->add_string = private_dtw_add_string;
    self->append_string_array = private_dtw_append_string_array;
    self->represent= private_dtw_represent_string_array;
    self->delete = private_dtw_delete_string_array;
    return self;
}


// Function prototypes
void private_dtw_add_string(struct DtwStringArray *self, char *string){
    self->size++;
    self->strings =  (char**)realloc(self->strings, self->size * sizeof(char *));
    self->strings[self->size - 1] = (char*)malloc(strlen(string) + 1);
    strcpy(self->strings[self->size - 1], string);
}

void private_dtw_append_string_array(struct DtwStringArray *self, struct DtwStringArray *other){
    for(int i = 0; i < other->size; i++){
        private_dtw_add_string(self, other->strings[i]);
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
