


struct  DtwTree * newDtwTree(){

    struct DtwTree *self = (struct DtwTree*)malloc(sizeof(struct DtwTree));
    self->size = 0;
    self->tree_parts = (struct DtwTreePart**)malloc(1);
    self->add_tree_part_by_copy = DtwTree_add_tree_part_copy;
    self->remove_tree_part = DtwTree_remove_tree_part;
    self->get_sub_tree = DtwTree_get_sub_tree;
    self->add_tree_part_by_reference = DtwTree_add_tree_part_reference;
    self->free = DtwTree_dtw_free_tree;
    self->represent = DtwTree_represent_tree;
    self->add_tree_parts_from_string_array = DtwTree_add_tree_parts_from_string_array;
    self->add_tree_from_hardware = DtwTree_add_tree_from_hardware;

    self->map = DtwTree_dtw_map;
    self->filter = DtwTree_dtw_filter;

    self->find_part_by_function = DtwTree_find_by_function;
    self->find_part_by_name  = DtwTree_find_tree_part_by_name;
    self->find_part_by_path = DtwTree_find_tree_part_by_path;
    self->report = DtwTree_create_report;
    
    self->list_files = DtwTree_list_files;
    self->list_dirs = DtwTree_list_dirs;
    self->list_all = DtwTree_list_all;

    self->list_files_recursively = DtwTree_list_files_recursively;
    self->list_dirs_recursively = DtwTree_list_dirs_recursively;
    self->list_all_recursively = DtwTree_list_all_recursively;
    
    self->loads_json_tree = DtwTree_loads_json_tree;
    self->loads_json_tree_from_file = DtwTree_loads_json_tree_from_file;
    
    self->dumps_json_tree = DtwTree_dumps_tree_json;
    self->dumps_json_tree_to_file = DtwTree_dumps_tree_json_to_file;

    //{%endif%}
    self->insecure_hardware_remove_tree = DtwTree_insecure_hardware_remove_tree;
    self->insecure_hardware_write_tree = DtwTree_insecure_hardware_write_tree;
    self->hardware_commit_tree = DtwTree_hardware_commit_tree;
    return self;
}


struct DtwTree *DtwTree_get_sub_tree(struct DtwTree *self, const char *path, bool copy_content){
    struct DtwTree *sub_tree = newDtwTree();
    for(int i = 0; i < self->size; i++){
        struct DtwTreePart *tree_part = self->tree_parts[i];
        char *current_path = tree_part->path->get_path(tree_part->path);
        if(dtw_starts_with(current_path,path)){
            if(copy_content){
                sub_tree->add_tree_part_by_copy(sub_tree,tree_part->self_copy(tree_part));
            }
            else{
                sub_tree->add_tree_part_by_reference(sub_tree,tree_part);

            }
        }
        free(current_path);
    }
    return sub_tree;
}


void DtwTree_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part){
    self->size++;
    self->tree_parts =  (struct DtwTreePart**)realloc(self->tree_parts, self->size * sizeof(struct DtwTreePart *));
    self->tree_parts[self->size - 1] = tree_part->self_copy(tree_part);
       
}
void DtwTree_remove_tree_part(struct DtwTree *self, int position){

    self->size--;
    self->tree_parts[position]->free(self->tree_parts[position]);

    for(int i = position; i<self->size; i++){
        self->tree_parts[i] = self->tree_parts[i+1];
    }


}

struct DtwTreeTransactionReport * DtwTree_create_report(struct DtwTree *self){
    struct DtwTreeTransactionReport *report = newDtwTreeTransactionReport();
    for(int i = 0; i < self->size; i++){
        struct DtwTreePart *tree_part = self->tree_parts[i];
        int pending_action = tree_part->pending_action;
        char *path = tree_part->path->get_path(tree_part->path);

        if (pending_action == DTW_WRITE){
            report->write->append(report->write, path);
        }

        else if (pending_action == DTW_MODIFY){
            report->modify->append(report->modify, path);
        }

        else if (pending_action == DTW_REMOVE){
            report->remove->append(report->remove, path);
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
        self->tree_parts[i]->represent(self->tree_parts[i]);
    }
}

void DtwTree_add_tree_parts_from_string_array(struct DtwTree *self, struct DtwStringArray *paths,DtwTreeProps *props){
    for(int i = 0; i < paths->size; i++){

        const char *current_path = paths->strings[i];
        struct DtwTreePart *tree_part = newDtwTreePart(
                current_path,
                props
        );
        
        self->add_tree_part_by_reference(self, tree_part);
    }
}


void DtwTree_add_tree_from_hardware(struct DtwTree *self,const char *path, DtwTreeProps *props){
    DtwTreeProps formated_props = DtwTreeProps_format_props(props);
    struct DtwStringArray *path_array = dtw_list_all_recursively(path,DTW_CONCAT_PATH);
    path_array->sort(path_array);
    self->add_tree_parts_from_string_array(self, path_array,props);
    path_array->free(path_array);


    if(formated_props.path_atributes == DTW_INCLUDE){
        return;
    }
    if(self->size == 0){
        return;
    }
    self->remove_tree_part(self,0);

    int size_to_remove = strlen(path);
    if(!dtw_ends_with(path,"/")){
        size_to_remove+=1;
    }

    for(int i =0; i < self->size; i++){
        struct DtwTreePart *current_part = self->tree_parts[i];
        struct DtwPath *current_path = current_part->path;
        char *current_path_string = current_path->get_path(current_path);
        //remove the size toremove from string

        memmove(
                current_path_string,
                current_path_string+size_to_remove,
                strlen(current_path_string) - size_to_remove +1
                );
        current_path->set_path(current_path,current_path_string);
        strcpy(current_path->original_path,current_path_string);
        free(current_path_string);
    }

}

void DtwTree_dtw_free_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        self->tree_parts[i]->free(self->tree_parts[i]);
    }
    
    free(self->tree_parts);
    free(self);
}
void DtwTree_insecure_hardware_remove_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        self->tree_parts[i]->hardware_remove(self->tree_parts[i],DTW_EXECUTE_NOW);
    }
}

void DtwTree_insecure_hardware_write_tree(struct DtwTree *self){
    
    for(int i = 0; i < self->size; i++){
        struct DtwTreePart *tree_part = self->tree_parts[i];
        tree_part->hardware_write(tree_part,DTW_EXECUTE_NOW);
    }
}

void DtwTree_hardware_commit_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        self->tree_parts[i]->hardware_commit(self->tree_parts[i]);
    }
}
