#pragma once
#include "extras.c"
#include "monodimension_listage.c"


char ** dtw_list_dirs_recursively(char *path, int *size){
        
        int actual_size = 0;    
        char **dirs = dtw_list_basic(path,&actual_size, "dir",true);

        int i = 0;
        while(i < actual_size){
                int size_of_sub_dirs;
                
                char **sub_dirs = dtw_list_basic(dirs[i],&size_of_sub_dirs,"dir",true);
                
                dtw_append_string_array_in_other(&dirs,&actual_size,sub_dirs,size_of_sub_dirs);
                dtw_free_string_array(sub_dirs,size_of_sub_dirs);
                i++;
                
        }
        //sort dirs by alphabetical order
        
        *size = actual_size;
        return dirs;

}