
char *dtw_concat_path(const char *path1, const char *path2);

DtwStringArray* private_dtw_remove_start_path(struct DtwStringArray *paths,const char *path_to_remove);

char *private_dtw_format_path(const char *path);

void private_dtw_remove_double_bars_from_string_array(struct DtwStringArray*path);

int private_dtw_string_cmp(const void *a, const void *b);

char * private_dtw_format_vaarg(const char *expresion, va_list args);

char *private_dtw_realoc_formatting(char *ptr,const char *format,...);