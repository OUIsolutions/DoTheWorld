
struct DtwStringArray * newDtwStringArray(){
    struct DtwStringArray *self = (struct DtwStringArray*)malloc(sizeof(struct DtwStringArray));
    self->size = 0;

    self->strings = (char**)malloc(1);
    self->ownership = (bool*)malloc(0);

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
void DtwStringArray_dtw_append(struct DtwStringArray *self,const  char *string,int ownership){

    self->strings =  (char**)realloc(self->strings, (self->size+ 1) * sizeof(char*));
    self->ownership = (bool*)realloc(self->ownership,(self->size+ 1) * sizeof(bool));
    self->ownership[self->size] = false;

    if(ownership == DTW_BY_OWNERSHIP || ownership == DTW_BY_VALUE){
        self->ownership[self->size] = true;
    }

    if(ownership == DTW_BY_REFERENCE || ownership == DTW_BY_OWNERSHIP){
        self->strings[self->size] = (char*)string;
    }

    else{

        int string_size = strlen(string);
        self->strings[self->size] = (char*)malloc(string_size + 1);
        self->strings[self->size][string_size] = '\0';
        strcpy(self->strings[self->size], string);

    }
    self->size+=1;
}


void DtwStringArray_dtw_merge_string_array(struct DtwStringArray *self, struct DtwStringArray *other){
    for(int i = 0; i < other->size; i++){
        self->append(self, other->strings[i],DTW_BY_VALUE);
    }
}


void DtwStringArray_dtw_represent_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        printf("%s\n", self->strings[i]);
    }
}

int string_cmp(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcmp(str_a, str_b);
}

void DtwStringArray_dtw_sort(struct DtwStringArray *self) {
    // Criar um array auxiliar para armazenar os pares (string, ownership)
    privateDtwStringOwnershipPair *pairs = (privateDtwStringOwnershipPair*)malloc(self->size * sizeof(struct privateDtwStringOwnershipPair));

    // Copiar as strings e os ownerships para o array auxiliar
    for (int i = 0; i < self->size; i++) {
        pairs[i].string = self->strings[i];
        pairs[i].ownership = self->ownership[i];
    }

    // Ordenar o array auxiliar com base nas strings
    qsort(pairs, self->size, sizeof(privateDtwStringOwnershipPair), private_dtw_string_cmp);

    // Copiar as strings ordenadas e os ownerships de volta para o array original
    for (int i = 0; i < self->size; i++) {
        self->strings[i] = pairs[i].string;
        self->ownership[i] = pairs[i].ownership;
    }

    free(pairs);
}


void DtwStringArray_dtw_free_string_array(struct DtwStringArray *self){
    for(int i = 0; i < self->size; i++){
        bool owner= self->ownership[i];
        if(owner){
            free(self->strings[i]);
        }
    }
    free(self->ownership);
    free(self->strings);
    free(self);
}
