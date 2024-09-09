

void dtw_create_dir_recursively(const char *path);

bool dtw_remove_any(const char* path);

char *dtw_get_current_dir();

long dtw_get_total_itens_of_dir(const char *path);

unsigned char *dtw_load_any_content(const char * path,long *size,bool *is_binary);

char *dtw_load_string_file_content(const char * path);

unsigned char *dtw_load_binary_content(const char * path,long *size);


bool dtw_write_any_content(const char *path,unsigned  char *content,long size);
bool dtw_write_string_file_content(const char *path,const char *content);



int dtw_entity_type(const char *path);



int dtw_complex_entity_type(const char *path);

const char *dtw_convert_entity(int entity_type);


bool dtw_copy_any(const char* src_path,const  char* dest_path,bool merge);



bool dtw_move_any(const char* src_path, const char* dest_path,bool merge);