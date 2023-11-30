//
// Created by jurandi on 11-04-2023.
//
struct DtwTreePart *DtwTree_find_tree_part_by_function(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part)
){
    for(int i = 0;i < self->size; i++){
        struct DtwTreePart *current = self->tree_parts[i];
        bool result = caller(current);
        if(result){
            return current;
        }
    }
    return NULL;
}

struct DtwTree *DtwTree_filter(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part)
){
    DtwTree *filtered_tree = newDtwTree();

    for(int i = 0;i < self->size; i++){

        DtwTreePart *current = self->tree_parts[i];

        bool result = caller(current);

        if(result){
            DtwTree_add_tree_part_copy(filtered_tree,current);
        }

    }
    return filtered_tree;
}


struct DtwTree *DtwTree_map(
        struct DtwTree *self,
        struct DtwTreePart *(*caller)(struct  DtwTreePart *part)
){
    struct DtwTree *mapped_tree = newDtwTree();

    for(int i = 0;i < self->size; i++){
        struct DtwTreePart *current = self->tree_parts[i];
        struct DtwTreePart *copy = DtwTreePart_self_copy(current);
        struct DtwTreePart *result = caller(copy);
        DtwTree_add_tree_part_by_reference(mapped_tree, result);
    }
    return mapped_tree;
}


struct DtwTreePart *DtwTree_find_tree_part_by_name(struct DtwTree *self, const char *name){
    for(int i = 0;i < self->size; i++){
        struct DtwTreePart *current = self->tree_parts[i];
        struct DtwPath *current_path = current->path;
        char *current_name = DtwPath_get_full_name(current_path);
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

struct DtwTreePart *DtwTree_find_tree_part_by_path(struct DtwTree *self, const char *path){
    for(int i = 0;i < self->size; i++){
        struct DtwTreePart *current = self->tree_parts[i];
        struct DtwPath *current_path = current->path;
        char *current_path_string = DtwPath_get_path(current_path);
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