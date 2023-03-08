

// {%from "functions/monodimension_listage.c" import monodimension_listage%}
//{% macro multidimension_listage() %}
struct DtwStringArray * dtw_list_dirs_recursively(char *path){
        //{{monodimension_listage()}}
        struct  DtwStringArray *dirs  = list_basic(path, "dir", true);
        int i = 0;
        //The size of dirs will increase til it reaches the end of the array
        while(i < dirs->size){                
                struct DtwStringArray *sub_dirs = list_basic(dirs->strings[i],"dir",true);
                //merge the two dirs
                dtw_append_string_array(dirs,sub_dirs);
                dtw_free_string_array(sub_dirs);
                i++;
        }
        return dirs;

}


struct DtwStringArray *  dtw_list_files_recursively(char *path){
    //{{monodimension_listage()}}
    struct DtwStringArray *dirs = dtw_list_dirs_recursively(path);
    
    struct  DtwStringArray *files = dtw_create_string_array();
    
    for(int i = 0; i < dirs->size; i++){
        struct DtwStringArray *sub_files = list_basic(dirs->strings[i],"file",true);
        dtw_append_string_array(files,sub_files);
        dtw_free_string_array(sub_files);
    }
    dtw_free_string_array(dirs);
    return files;
}

//{% endmacro %}