
// {%from "functions/monodimension_listage.c" import monodimension_listage%}

//{% macro create_wrappers() %}

//Included in code/functions/listage_wrappers.c

struct DtwStringArray * dtw_list_files(char *path, bool concat_path){
    //{{monodimension_listage()}}
    return list_basic(path,  "file", concat_path);
}

struct DtwStringArray * dtw_list_dirs(char *path, bool concat_path){
     //{{monodimension_listage()}}
    return list_basic(path,"dir", concat_path);
}

struct DtwStringArray *  dtw_list_all(char *path,  bool concat_path){
    //{{monodimension_listage()}}
    return list_basic(path, "all", concat_path);
}
// End of code/functions/listage_wrappers.c
//{%- endmacro %}