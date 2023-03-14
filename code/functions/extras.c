
char * dtw_generate_sha_from_file(const char *path){
    return calc_sha_256_from_file_returning_string(path);
}


char * dtw_generate_sha_from_string(const char *string){
    return calc_sha_256_from_string_returning_string(string);
}


long int dtw_get_file_last_motification_in_unix(const char *path){
    struct stat attr;
    stat(path, &attr);
    // convert to unix time
    time_t last_modification_in_unix = attr.st_mtime;
    return last_modification_in_unix;
}

char * dtw_convert_unix_time_to_string(long int unix_time){
    struct tm * timeinfo;
    timeinfo = localtime(&unix_time);
    char *time_string = (char *)malloc(100);
    strftime(time_string, 100, "%Y-%m-%d %H:%M:%S", timeinfo);
    return time_string;
}

char * dtw_get_file_last_motification_in_string(const char *path){
    long int last_modification_in_unix = dtw_get_file_last_motification_in_unix(path);
    char *last_modification_in_string = dtw_convert_unix_time_to_string(last_modification_in_unix);
    return last_modification_in_string;
}


bool dtw_starts_with(const char *string, const char *prefix){
    if(strncmp(string, prefix, strlen(prefix)) == 0){
        return true;
    }
    return false;
}

bool dtw_ends_with(const char *string, const char *suffix){
    if(strlen(string) < strlen(suffix)){
        return false;
    }
    if(strcmp(string + strlen(string) - strlen(suffix), suffix) == 0){
        return true;
    }
    return false;
}

char *private_dtw_replace_string_once(const char *target, const char *old_element, const char *new_element) {

    const char *pos = strstr(target, old_element);

    int size_of_old_element = strlen(old_element);
    int size_of_new_element = strlen(new_element);
    // Allocate memory for the new string
    char *result = (char *)malloc(strlen(target) + size_of_new_element - size_of_old_element + 1);

    // Copy the part of the original string before the old substring
    strncpy(result, target, pos - target);

    // Copy the new substring to the result string
    strcpy(result + (pos - target), new_element);

    // Copy the rest of the original string after the old substring
    strcpy(result + (pos - target) + size_of_new_element, pos + size_of_old_element);

    return result;

    

}

char* dtw_replace_string(const char *target, const char *old_element, const char *new_element) {
    char *result = (char *)malloc(strlen(target) + 1);
    strcpy(result, target);
    char *temp = NULL;
    while (strstr(result, old_element) != NULL) {
        temp = private_dtw_replace_string_once(result, old_element, new_element);
        free(result);
        result = temp;
    }
    return result;
}

char *dtw_change_beginning_of_string(const char *target,int size, const char *new_element) {
    char *result = (char *)malloc(strlen(target) + size + 1);
    strcpy(result, new_element);
    strcat(result, target + size);
    return result;
}


void private_dtw_add_end_bar_to_dirs_string_array(struct DtwStringArray * dirs){
    for(int i = 0; i < dirs->size; i++){
        if(!dtw_ends_with(dirs->strings[i], "/")){
             char *formated_dir =  (char*)malloc(strlen(dirs->strings[i]) + 2);
             sprintf(formated_dir,"%s/",dirs->strings[i]);
             dirs->set_value(dirs,i,formated_dir);
             free(formated_dir);
        }
    }
}