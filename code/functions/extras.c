
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



