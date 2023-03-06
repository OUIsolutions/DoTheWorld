
struct DtwStringArray {
  int size;         
  char **strings;       
}; // End the structure with a semicolon

// Function prototypes
void dtw_add_string(struct DtwStringArray *array, char *string){
    array->size++;
    array->strings = realloc(array->strings, array->size * sizeof(char *));
    array->strings[array->size - 1] = string;
}

void dtw_represent_string_array(struct DtwStringArray *array){
    for(int i = 0; i < array->size; i++){
        printf("%s", array->strings[i]);
    }
}