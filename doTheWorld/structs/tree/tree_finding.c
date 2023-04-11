//
// Created by jurandi on 11-04-2023.
//
struct DtwTreePart *private_dtw_find_by_function(
        struct DtwTree *self,
        bool (*filter)(struct  DtwTreePart *part)
){
    for(int i = 0;i < self->size; i++){
        struct DtwTreePart *current = self->tree_parts[i];
        bool result = filter(current);
        if(result){
            return current;
        }
    }
    return NULL;
}


struct DtwTreePart *private_dtw_find_tree_part_by_name(struct DtwTree *self,const char *name){
    for(int i = 0;i < self->size; i++){
        struct DtwTreePart *current = self->tree_parts[i];
        struct DtwPath *current_path = current->path;
        char *current_name = current_path->get_full_name(current_path);
        if(current_name){

            if(strcmp(current_name, name) == 0){
                free(current_name);
                return current;
            }
            free(current_name);
        }

    }

    return NULL;
}

struct DtwTreePart *private_dtw_find_tree_part_by_path(struct DtwTree *self,const char *path){
    for(int i = 0;i < self->size; i++){
        struct DtwTreePart *current = self->tree_parts[i];
        struct DtwPath *current_path = current->path;
        char *current_path_string = current_path->get_path(current_path);
        if(current_path_string){
            if(strcmp(current_path_string, path) == 0){
                free(current_path_string);
                return current;
            }
            free(current_path_string);
        }

    }

    return NULL;
}