

struct DtwStringArray * dtw_list_dirs_recursively(const char *path,bool add_end_bar_to_dir){

        struct  DtwStringArray *dirs  = dtw_constructor_string_array();
        //verify if the path is a directory
        if( opendir(path)== NULL){
                return dirs;
        }
        dirs->add_string(dirs,path);

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
                sub_dirs->delete_string_array(sub_dirs);
                i++;
        }
        //unsifth path in dirs 
        
        
        if(add_end_bar_to_dir){
        for(int i = 0; i < dirs->size; i++){
                char *dir = dirs->strings[i];
                char *new_dir = (char*)malloc(strlen(dir) + 1);
                //concat '/' to the end of the directory
                sprintf(new_dir, "%s/", dir);
                free(dirs->strings[i]);
                dirs->strings[i] = new_dir;
            }
        }

        return dirs;
}



struct DtwStringArray *  dtw_list_files_recursively(const char *path){
    
    struct DtwStringArray *dirs = dtw_list_dirs_recursively(path,false);
    
    struct  DtwStringArray *files = dtw_constructor_string_array();
    
    for(int i = 0; i < dirs->size; i++){
        struct DtwStringArray *sub_files = dtw_list_basic(dirs->strings[i],DTW_FILE_TYPE,true,false);
        files->merge_string_array(files,sub_files);
        sub_files->delete_string_array(sub_files);
    }
    dirs->delete_string_array(dirs);
    return files;
}

struct DtwStringArray * dtw_list_all_recursively(const char *path,bool add_end_bar_to_dir){

    struct DtwStringArray *dirs = dtw_list_dirs_recursively(path,false);
    
    struct DtwStringArray *all = dtw_constructor_string_array();
    
    for(int i = 0; i < dirs->size; i++){
        if(add_end_bar_to_dir){
            char *formated_dir =  (char*)malloc(strlen(dirs->strings[i]) + 1);
            sprintf(formated_dir,"%s/",dirs->strings[i]);
            all->add_string(all,formated_dir);
        }
        else{
            all->add_string(all,dirs->strings[i]);
        }

        struct DtwStringArray *sub_files = dtw_list_basic(dirs->strings[i],DTW_FILE_TYPE,true,false);
        all->merge_string_array(all,sub_files);
    }
    dirs->delete_string_array(dirs);
    return all;
}