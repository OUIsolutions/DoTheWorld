
struct DtwStringArray * dtw_list_dirs_recursively(const char *path){

        struct  DtwStringArray *dirs  = dtw_constructor_string_array();
        //verify if the path is a directory
        
        DIR *dir = opendir(path);
        if( dir == NULL){
                return dirs;
        }
        closedir(dir);
        
        dirs->add_string(dirs,path);

        int i = 0;
        //The size of dirs will increase til it reaches the end of the array
        while(i < dirs->size){                
                struct DtwStringArray *sub_dirs = dtw_list_basic(
                    dirs->strings[i],
                    DTW_FOLDER_TYPE,
                    true
                    );
                //merge the two dirs
                dirs->merge_string_array(dirs,sub_dirs);
                sub_dirs->free_string_array(sub_dirs);
                i++;
               
        }
        //unsifth path in dirs 
        
        
        private_dtw_add_end_bar_to_dirs_string_array(dirs);
        

        return dirs;
}



struct DtwStringArray *  dtw_list_files_recursively(const char *path){
    
    struct DtwStringArray *dirs = dtw_list_dirs_recursively(path);
    
    struct  DtwStringArray *files = dtw_constructor_string_array();
    
    for(int i = 0; i < dirs->size; i++){
        struct DtwStringArray *sub_files = dtw_list_basic(dirs->strings[i],DTW_FILE_TYPE,true);
        files->merge_string_array(files,sub_files);
        sub_files->free_string_array(sub_files);
    }
    dirs->free_string_array(dirs);
    return files;
}
struct DtwStringArray * dtw_list_all_recursively(const char *path){

    struct DtwStringArray *dirs = dtw_list_dirs_recursively(path);
    
    struct DtwStringArray *all = dtw_constructor_string_array();
    
    for(int i = 0; i < dirs->size; i++){
     
        char *formated_dir =  (char*)malloc(strlen(dirs->strings[i]) + 2);
        sprintf(formated_dir,"%s/",dirs->strings[i]);
        all->add_string(all,formated_dir);
        free(formated_dir);
    
        struct DtwStringArray *sub_files = dtw_list_basic(dirs->strings[i],DTW_FILE_TYPE,true);
        all->merge_string_array(all,sub_files);
        sub_files->free_string_array(sub_files);
    }
    dirs->free_string_array(dirs);
    return all;
}