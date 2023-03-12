

struct DtwStringArray * dtw_list_files(char *path, bool concat_path){
    #include "monodimension_listage_linux.c"
    #include "monodimension_listage_win32.c"
    return dtw_list_basic(path,  DTW_FILE_TYPE, concat_path);
}

struct DtwStringArray * dtw_list_dirs(char *path, bool concat_path){
    #include "monodimension_listage_linux.c"
    #include "monodimension_listage_win32.c"
    return dtw_list_basic(path,DTW_FOLDER_TYPE, concat_path);
}

struct DtwStringArray *  dtw_list_all(char *path,  bool concat_path){
    #include "monodimension_listage_linux.c"
    #include "monodimension_listage_win32.c"
    return dtw_list_basic(path, DTW_ALL_TYPE, concat_path);
}
