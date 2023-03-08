#include "monodimension_listage.c" 


//{% macro create_wrappers() -%}

struct DtwStringArray * dtw_list_files(char *path, bool concat_path){
    return dtw_list_basic(path,  "file", concat_path);
}

struct DtwStringArray * dtw_list_dirs(char *path, bool concat_path){
    return dtw_list_basic(path,"dir", concat_path);
}

struct DtwStringArray *  dtw_list_all(char *path,  bool concat_path){
    return dtw_list_basic(path, "all", concat_path);
}
//{%- endmacro %}