
struct DtwTreePart{

    char *path;
    char * sha256;
    unsigned char *content;
    unsigned int last_modification_in_unix;
    unsigned int size;
    bool ignore_all;
    bool ignore_content;

};

void dtw_set_tree_part_content(struct DtwTreePart *self, char *content,bool set_time){
    self->content = (char*)realloc(self->content,strlen(content) + 1);
    uint8_t hash[32];
    calc_sha_256(hash,content,strlen(content));
    self->sha256 = (char*)realloc(self->sha256,65);
    for(int i = 0; i < 32; i++){
        sprintf(self->sha256 + (i * 2), "%02x", hash[i]);
    }
    self->size = strlen(content);
    if(set_time){
        //set time as now
        time_t now = time(NULL);
        self->last_modification_in_unix = now;
    
    }
    strcpy(self->content,content);
}

void dtw_load_tree_part_content(struct DtwTreePart *self, char *path){
    char *content = dtw_load_file_content(path);
    dtw_set_tree_part_content(self,content,false);
    struct stat info;
    stat(path,&info);
    self->last_modification_in_unix = info.st_mtime;
    free(content);
}

struct  DtwTreePart * dtw_create_tree_part(char *path,bool load_content){
    struct DtwTreePart *self = (struct DtwTreePart*)malloc(sizeof(struct DtwTreePart));
    self->size = 0;
    self->path = (char*)malloc(strlen(path) + 1);
    strcpy(self->path, path);
    self->sha256 = (char*)malloc(0);
    self->content = (char*)malloc(0);
    self->last_modification_in_unix = 0;
    self->size = 0;
    self->ignore_all = false;
    self->ignore_content = false;
    if(load_content){
        dtw_load_tree_part_content(self,path);
    }   
    return self;
}

void dtw_represent_tree_part(struct DtwTreePart *self){
    printf("-------------------------------------------\n");
    printf("Path: %s\n", self->path);
    printf("SHA256: %s\n", self->sha256);
    printf("Size: %d\n", self->size);
    //convert time to human readable
    time_t t = self->last_modification_in_unix;
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "%c", tm);
    printf("Last modification: %s\n", s);

    free(tm);
    
    printf("Content:\n%s", self->content);

}

void dtw_free_tree_part(struct DtwTreePart *self){
    free(self->path);
    free(self->content);
    free(self);
}
