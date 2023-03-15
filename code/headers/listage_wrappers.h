

struct DtwStringArray * dtw_list_files(char *path, bool concat_path);
struct DtwStringArray * dtw_list_dirs(char *path, bool concat_path, bool add_end_bar_to_dir);

struct DtwStringArray *  dtw_list_all(char *path,  bool concat_path, bool add_end_bar_to_dir);