#include "extras.c"
#include "monodimension_listage.c"

char ** cfm_list_dirs_recursively(char *path, int *size){
        

        int actual_size = 0;    
        char **dirs = cfm_list_basic(path,&actual_size, "dir",true);
        dirs = realloc(dirs, (30) * sizeof(char*));

        int i = 0;
        while(i < actual_size -2){
                int size2;
                char **dirs2 = cfm_list_basic(dirs[i],&size2,"dir",true);
                
               
                for(int j = 0; j < size2; j++){       
                        dirs[actual_size + j] = malloc(strlen(dirs2[j]) + 1);
                        strcpy(dirs[actual_size + j], dirs2[j]);
                }        
                actual_size += size2;
             
                cfm_free_string_array(dirs2,size2);
                i++;
                
        }
        *size = actual_size;
        return dirs;


}