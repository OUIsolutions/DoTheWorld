
struct  DtwTree{
    int size;
    struct DtwTreePart **tree_parts;
    void (*add_tree_part_by_copy)(struct DtwTree *self, struct DtwTreePart *tree_part);
    void (*delete_tree)(struct DtwTree *self);
    void(*represent)(struct DtwTree *self);
};
void private_dtw_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part);
void private_dtw_delete_tree(struct DtwTree *self);
void private_dtw_represent_tree(struct DtwTree *self);


struct  DtwTree * dtw_tree_constructor(){
    struct DtwTree *self = (struct DtwTree*)malloc(sizeof(struct DtwTree));
    self->size = 0;
    self->tree_parts = (struct DtwTreePart**)malloc(1);
    self->add_tree_part_by_copy = private_dtw_add_tree_part_copy;
    self->delete_tree = private_dtw_delete_tree;
    self->represent = private_dtw_represent_tree;
    return self;
}

void private_dtw_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part){
    self->size++;
    self->tree_parts =  (struct DtwTreePart**)realloc(self->tree_parts, self->size * sizeof(struct DtwTreePart *));
    self->tree_parts[self->size - 1] = tree_part->copy_tree_part(tree_part);
    
    
}

void private_dtw_delete_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        self->tree_parts[i]->delete_tree_part(self->tree_parts[i]);
    }
    free(self);
}

void private_dtw_represent_tree(struct DtwTree *self){
    for(int i = 0; i < self->size; i++){
        self->tree_parts[i]->represent(self->tree_parts[i]);
    }
}
