#include "extras.c"
#include "monodimension_listage.c"

char ** cfm_list_dirs_recursively(char *path, int *size){
        
        int actual_size = 0;    
        char **dirs = cfm_list_basic(path,&actual_size, "dir",true);

        int i = 0;
        while(i < actual_size){
                int size_of_sub_dirs;
                
                char **sub_dirs = cfm_list_basic(dirs[i],&size_of_sub_dirs,"dir",true);
                
                //realocate memory with the new size
                dirs = realloc(dirs, (actual_size + size_of_sub_dirs) * sizeof(char*));                

                //merge the dirs with the sub_dirs
                for(int j = 0; j < size_of_sub_dirs; j++){       
                        dirs[actual_size + j] = malloc(strlen(sub_dirs[j]) + 1);
                        strcpy(dirs[actual_size + j], sub_dirs[j]);
                }        

                actual_size += size_of_sub_dirs;
             
                cfm_free_string_array(sub_dirs,size_of_sub_dirs);
                i++;
                
        }
        //sort dirs by alphabetical order
        
        *size = actual_size;
        return dirs;

}