


struct  DtwTree * dtw_tree_constructor(){
    struct DtwTree *self = (struct DtwTree*)malloc(sizeof(struct DtwTree));
    self->size = 0;
    self->tree_parts = (struct DtwTreePart**)malloc(1);
    self->add_tree_part_by_copy = private_dtw_add_tree_part_copy;
    self->add_tree_part_by_reference = private_dtw_add_tree_part_reference;
    self->delete_tree = private_dtw_delete_tree;
    self->represent = private_dtw_represent_tree;
    self->add_path_from_hardware = private_dtw_add_path_from_hardware;
    self->loads_json_tree = private_dtw_loads_json_tree;
    self->dumps_json_tree = private_dtw_dumps_tree_json;
    return self;
}


void private_dtw_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part){
    self->size++;
    self->tree_parts =  (struct DtwTreePart**)realloc(self->tree_parts, self->size * sizeof(struct DtwTreePart *));
    self->tree_parts[self->size - 1] = tree_part->copy_tree_part(tree_part);
       
}
void private_dtw_add_tree_part_reference(struct DtwTree *self, struct DtwTreePart *tree_part){
    self->size++;
    self->tree_parts =  (struct DtwTreePart**)realloc(self->tree_parts, self->size * sizeof(struct DtwTreePart *));
    self->tree_parts[self->size - 1] = tree_part;
}


void private_dtw_delete_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        self->tree_parts[i]->delete_tree_part(self->tree_parts[i]);
    }
    free(self->tree_parts);
    
    free(self);
}

void private_dtw_represent_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        self->tree_parts[i]->represent(self->tree_parts[i]);
    }
}
void private_dtw_add_path_from_hardware(struct DtwTree *self,const char *path,bool load_content, bool preserve_content){
    
    struct DtwStringArray *path_array = dtw_list_all_recursively(path, true);
    for(int i = 0; i < path_array->size; i++){
        const char *current_path = path_array->strings[i];

        
        struct DtwTreePart *tree_part = dtw_tree_part_constructor(
            current_path,
            load_content,
            preserve_content
        );
        self->add_tree_part_by_reference(self, tree_part);
        
    }

    path_array->delete_string_array(path_array);

}
