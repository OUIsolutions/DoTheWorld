
void private_dtw_remove_double_bars_from_string_array(struct DtwStringArray*path){
    for(int i =0;i< path->size;i++){
        char *current_string = path->strings[i];
        char *result = dtw_replace_string(current_string,"//","/");
        strcpy(current_string,result);
        free(result);
    }
}
char *dtw_concat_path(const char *path1, const char *path2){

    if(!path1){
        return strdup(path2);
    }

    if(!path2){
        return strdup(path1);
    }

    char *path = (char *)malloc(strlen(path1) + strlen(path2) + 3);

    if(dtw_ends_with(path1, "/") || dtw_ends_with(path1, "\\")){
        sprintf(path,"%s%s",path1,path2);

    }
    else{
        sprintf(path,"%s/%s",path1,path2);

    }
    return path;
}

char * private_dtw_format_vaarg(const char *expresion, va_list args){

    va_list args_copy;
    va_copy(args_copy, args);
    long required_size = vsnprintf(NULL, 0,expresion,args_copy);
    va_end(args_copy);
    char *buffer = (char*)malloc(sizeof(char) * required_size + 2);
    vsnprintf(buffer,sizeof (char) * required_size+1,expresion,args);
    return buffer;
}

char *private_dtw_format_path(const char *path){
    int path_size = (int)strlen(path);
    char *buffer = malloc((path_size+2) * sizeof(char));
    int buffer_size = 0;
    bool already_concatened = false;
    for(long i = 0; i < path_size;i++){
        char current_char = path[i];

        bool is_a_divisor =current_char == '\\' || current_char == '/';

        if(is_a_divisor && already_concatened){
            continue;
        }
        if(is_a_divisor){
            #ifdef __linux
            buffer[buffer_size] = '/';
            #else
            buffer[buffer_size] = '\\';
            #endif
                buffer_size+=1;
                already_concatened = true;
            continue;
        }

        already_concatened = false;
        buffer[buffer_size] = current_char;
        buffer_size+=1;

    }
    buffer[buffer_size] = '\0';
    return buffer;
}
int private_dtw_string_cmp(const void *a, const void *b){
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcmp(str_a, str_b);
}
