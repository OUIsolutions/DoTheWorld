

char * dtw_generate_content_sha_from_any(char * content,int *size){
    #include "../dependencies/sha-256.c"
    return calc_sha_256_returning_string(content,size);
}

char * dtw_generate_content_sha_from_string(char * content){
    #include "../dependencies/sha-256.c"
    return calc_sha_256_returning_string(content,NULL);
}
