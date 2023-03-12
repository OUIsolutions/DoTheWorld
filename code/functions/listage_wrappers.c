

struct DtwStringArray * dtw_list_files(char *path, bool concat_path){
    return dtw_list_basic(path,  DTW_FILE_TYPE, concat_path, false);
}

struct DtwStringArray * dtw_list_dirs(char *path, bool concat_path, bool add_end_bar_to_dir){
    return dtw_list_basic(path,DTW_FOLDER_TYPE, concat_path, add_end_bar_to_dir);
}

struct DtwStringArray *  dtw_list_all(char *path,  bool concat_path, bool add_end_bar_to_dir){
    return dtw_list_basic(path, DTW_ALL_TYPE, concat_path, add_end_bar_to_dir);
}
