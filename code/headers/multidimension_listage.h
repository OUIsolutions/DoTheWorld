
#ifdef __cplusplus
struct DtwStringArray * dtw_list_dirs_recursively(const char *path,bool add_end_bar_to_dir=true);
#else 
struct DtwStringArray * dtw_list_dirs_recursively(const char *path,bool add_end_bar_to_dir);
#endif
  

struct DtwStringArray *  dtw_list_files_recursively(const char *path);

#ifdef __cplusplus
struct DtwStringArray * dtw_list_all_recursively(const char *path,bool add_end_bar_to_dir=true);
#else 
struct DtwStringArray * dtw_list_all_recursively(const char *path,bool add_end_bar_to_dir);
#endif
