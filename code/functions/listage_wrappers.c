

struct DtwStringArray * dtw_list_files(char *path, bool concat_path){
    //{%include"functions/monodimension_listage.c"%}
    return list_basic(path,  "file", concat_path);
}

struct DtwStringArray * dtw_list_dirs(char *path, bool concat_path){
    //{%include"functions/monodimension_listage.c"%}
    return list_basic(path,"dir", concat_path);
}

struct DtwStringArray *  dtw_list_all(char *path,  bool concat_path){
    //{%include"functions/monodimension_listage.c"%}
    return list_basic(path, "all", concat_path);
}
