


struct  DtwTree * newDtwTree(){

    struct DtwTree *self = (struct DtwTree*)malloc(sizeof(struct DtwTree));
    self->size = 0;
    self->tree_parts = (struct DtwTreePart**)malloc(1);

    return self;
}


struct DtwTree *DtwTree_get_sub_tree(struct DtwTree *self, const char *path, bool copy_content){
    struct DtwTree *sub_tree = newDtwTree();
    for(int i = 0; i < self->size; i++){
        struct DtwTreePart *tree_part = self->tree_parts[i];
        char *current_path =  DtwPath_get_path(tree_part->path);
        if(dtw_starts_with(current_path,path)){
            if(copy_content){
                DtwTree_add_tree_part_copy(sub_tree,DtwTreePart_self_copy(tree_part));
            }
            else{
                DtwTree_add_tree_part_reference(sub_tree,tree_part);

            }
        }
        free(current_path);
    }
    return sub_tree;
}


void DtwTree_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part){
    self->size++;
    self->tree_parts =  (struct DtwTreePart**)realloc(self->tree_parts, self->size * sizeof(struct DtwTreePart *));
    self->tree_parts[self->size - 1] = DtwTreePart_self_copy(tree_part);
       
}
void DtwTree_remove_tree_part(struct DtwTree *self, int position){

    self->size--;
    DtwTreePart_free(self->tree_parts[position]);

    for(int i = position; i<self->size; i++){
        self->tree_parts[i] = self->tree_parts[i+1];
    }


}

struct DtwTreeTransactionReport * DtwTree_create_report(struct DtwTree *self){
    struct DtwTreeTransactionReport *report = newDtwTreeTransactionReport();
    for(int i = 0; i < self->size; i++){
        struct DtwTreePart *tree_part = self->tree_parts[i];
        int pending_action = tree_part->pending_action;
        char *path = DtwPath_get_path(tree_part->path);

        if (pending_action == DTW_WRITE){
            DtwStringArray_append(report->write, path);
        }

        else if (pending_action == DTW_MODIFY){
            DtwStringArray_append(report->modify, path);
        }

        else if (pending_action == DTW_REMOVE){
            DtwStringArray_append(report->remove, path);
        }

        free(path);
    
    }
    return report;
}


void DtwTree_add_tree_part_reference(struct DtwTree *self, struct DtwTreePart *tree_part){
    self->size++;
    self->tree_parts =  (struct DtwTreePart**)realloc(self->tree_parts, self->size * sizeof(struct DtwTreePart *));
    self->tree_parts[self->size - 1] = tree_part;
}


void DtwTree_represent_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        DtwTreePart_represent(self->tree_parts[i]);
    }
}

void DtwTree_add_tree_parts_from_string_array(struct DtwTree *self, struct DtwStringArray *paths,DtwTreeProps *props){
    for(int i = 0; i < paths->size; i++){

        const char *current_path = paths->strings[i];
        struct DtwTreePart *tree_part = newDtwTreePart(
                current_path,
                props
        );
        
        DtwTree_add_tree_part_reference(self, tree_part);
    }
}


void DtwTree_add_tree_from_hardware(struct DtwTree *self,const char *path, DtwTreeProps *props){
    DtwTreeProps formated_props = DtwTreeProps_format_props(props);
    struct DtwStringArray *path_array = dtw_list_all_recursively(path,DTW_CONCAT_PATH);
    DtwStringArray_sort(path_array);
    DtwTree_add_tree_parts_from_string_array(self, path_array,props);
    DtwStringArray_free(path_array);


    if(formated_props.path_atributes == DTW_INCLUDE){
        return;
    }
    if(self->size == 0){
        return;
    }
    DtwTree_remove_tree_part(self,0);

    int size_to_remove = strlen(path);
    if(!dtw_ends_with(path,"/")){
        size_to_remove+=1;
    }

    for(int i =0; i < self->size; i++){
        struct DtwTreePart *current_part = self->tree_parts[i];
        struct DtwPath *current_path = current_part->path;
        char *current_path_string = DtwPath_get_path(current_path);
        //remove the size toremove from string

        memmove(
                current_path_string,
                current_path_string+size_to_remove,
                strlen(current_path_string) - size_to_remove +1
                );
        DtwPath_set_path(current_path,current_path_string);
        strcpy(current_path->original_path,current_path_string);
        free(current_path_string);
    }

}

void DtwTree_dtw_free_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        DtwTreePart_free(self->tree_parts[i]);
    }
    
    free(self->tree_parts);
    free(self);
}
void DtwTree_insecure_hardware_remove_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        DtwTreePart_hardware_remove(self->tree_parts[i],DTW_EXECUTE_NOW);
    }
}

void DtwTree_insecure_hardware_write_tree(struct DtwTree *self){
    
    for(int i = 0; i < self->size; i++){
        struct DtwTreePart *tree_part = self->tree_parts[i];
        DtwTreePart_hardware_write(tree_part,DTW_EXECUTE_NOW);
    }
}

void DtwTree_hardware_commit_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        DtwTreePart_hardware_commit(self->tree_parts[i]);
    }
}
