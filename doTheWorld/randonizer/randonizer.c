



DtwRandonizer * newDtwRandonizer(){
    DtwRandonizer *self = (DtwRandonizer*) malloc(sizeof (DtwRandonizer));
    self->seed = dtw_get_time();
    self->actual_generation = 0;

    return self;
}

char * DtwRandonizer_generate_token(struct DtwRandonizer*self, int size){
    self->actual_generation+=1;
    static const char chars[] =
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789";

    int total_size = sizeof(chars) - 1;
    char *token = (char*)malloc(size +1);

    srand(  self->seed + self->actual_generation);

    for (int i = 0; i < size; ++i) {
        int index = rand() % total_size;
        token[i] = chars[index];
    }

    token[size] = '\0';
    return token;
}

void DtwRandonizer_free(struct DtwRandonizer *self){
    free(self);
}

