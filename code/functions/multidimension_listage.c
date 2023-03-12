

struct DtwStringArray * dtw_list_dirs_recursively(const char *path,bool add_bar_to_dir){

        struct  DtwStringArray *dirs  = dtw_list_basic(path,DTW_FOLDER_TYPE, true,false);
       
    
        int i = 0;
        //The size of dirs will increase til it reaches the end of the array
        while(i < dirs->size){                
                struct DtwStringArray *sub_dirs = dtw_list_basic(
                    dirs->strings[i],
                    DTW_FOLDER_TYPE,
                    true,
                    false
                    );
                //merge the two dirs
                dirs->merge_string_array(dirs,sub_dirs);
                sub_dirs->delete(sub_dirs);
                i++;
        }
        //unsifth path in dirs 
        struct DtwStringArray *new_dirs = dtw_constructor_string_array();
        new_dirs->add_string(new_dirs,path);
        new_dirs->merge_string_array(new_dirs,dirs);
        dirs->delete(dirs);

        if(add_bar_to_dir){
        for(int i = 0; i < new_dirs->size; i++){
                char *dir = new_dirs->strings[i];
                char *new_dir = (char*)malloc(strlen(dir) + 1);
                //concat '/' to the end of the directory
                sprintf(new_dir, "%s/", dir);
                free(new_dirs->strings[i]);
                new_dirs->strings[i] = new_dir;
            }
        }

    
        return new_dirs;
}



struct DtwStringArray *  dtw_list_files_recursively(const char *path){
    
    struct DtwStringArray *dirs = dtw_list_dirs_recursively(path,false);
    
    struct  DtwStringArray *files = dtw_constructor_string_array();
    
    for(int i = 0; i < dirs->size; i++){
        struct DtwStringArray *sub_files = dtw_list_basic(dirs->strings[i],DTW_FILE_TYPE,true,false);
        files->merge_string_array(files,sub_files);
        sub_files->delete(sub_files);
    }
    dirs->delete(dirs);
    return files;
}

