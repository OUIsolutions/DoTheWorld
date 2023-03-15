
char * dtw_generate_sha_from_file(const char *path);
char * dtw_generate_sha_from_string(const char *string);
long int dtw_get_file_last_motification_in_unix(const char *path);
char * dtw_convert_unix_time_to_string(long int unix_time);
char * dtw_get_file_last_motification_in_string(const char *path);
bool dtw_starts_with(const char *string, const char *prefix);
bool dtw_ends_with(const char *string, const char *suffix);

char *private_dtw_replace_string_once(const char *target, const char *old_element, const char *new_element);

char* dtw_replace_string(const char *target, const char *old_element, const char *new_element);


char *dtw_change_beginning_of_string(const char *target,int start_element_to_remove_size, const char *new_element);



void private_dtw_add_end_bar_to_dirs_string_array(struct DtwStringArray * dirs);