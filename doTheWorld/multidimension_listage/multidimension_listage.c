
struct DtwStringArray * dtw_list_dirs_recursively(const char *path,bool concat_path){

        struct  DtwStringArray *dirs  = newDtwStringArray();
        //verify if the path is a directory
    
        int entity_type = dtw_entity_type(path);
        if(entity_type != DTW_FOLDER_TYPE){
                return dirs;
        }
      
        
        dirs->append(dirs, (char*)path,DTW_BY_VALUE);

        private_dtw_add_end_bar_to_dirs_string_array(dirs);
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
                sub_dirs->free(sub_dirs);
                i++;
               
        }
        //unsifth path in dirs 
        private_dtw_remove_double_bars(dirs);

        if(!concat_path){

            struct DtwStringArray *removed =  private_dtw_remove_start_path(dirs,path);
            dirs->free(dirs);
            return removed;
        }
        return dirs;
}



struct DtwStringArray *  dtw_list_files_recursively(const char *path,bool concat_path){
    
    struct DtwStringArray *dirs = dtw_list_dirs_recursively(path,DTW_CONCAT_PATH);
    
    struct  DtwStringArray *files = newDtwStringArray();
    for(int i = 0; i < dirs->size; i++){
        struct DtwStringArray *sub_files = dtw_list_basic(dirs->strings[i],DTW_FILE_TYPE,DTW_CONCAT_PATH);
        files->merge_string_array(files,sub_files);
        sub_files->free(sub_files);
    }

    dirs->free(dirs);

    if(!concat_path){

        struct DtwStringArray *removed =  private_dtw_remove_start_path(files,path);
        files->free(files);
        return removed;
    }

    return files;
}


struct DtwStringArray * dtw_list_all_recursively(const char *path,bool concat_path){

    struct DtwStringArray *dirs = dtw_list_dirs_recursively(path,DTW_CONCAT_PATH);
    
    struct DtwStringArray *all = newDtwStringArray();
    
    for(int i = 0; i < dirs->size; i++){

        if(!dtw_ends_with(dirs->strings[i], "/") || !dtw_ends_with(dirs->strings[i], "\\") ){

            char *formated_dir =  (char*)malloc(strlen(dirs->strings[i]) + 2);
            sprintf(formated_dir,"%s/",dirs->strings[i]);
            all->append(all, formated_dir,DTW_BY_OWNERSHIP);

        }

        else{
            all->append(all, dirs->strings[i],DTW_BY_VALUE);
        }

        struct DtwStringArray *sub_files = dtw_list_basic(dirs->strings[i],DTW_FILE_TYPE,true);
        all->merge_string_array(all,sub_files);
        sub_files->free(sub_files);
    }
    dirs->free(dirs);
    private_dtw_remove_double_bars(all);
    if(!concat_path){

        struct DtwStringArray *removed =  private_dtw_remove_start_path(all,path);
        all->free(all);
        return removed;
    }
    return all;
}