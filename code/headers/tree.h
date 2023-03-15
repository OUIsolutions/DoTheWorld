
struct  DtwTree{
    int size;
    struct DtwTreePart **tree_parts;
    void (*add_tree_part_by_copy)(struct DtwTree *self, struct DtwTreePart *tree_part);
    void (*add_tree_part_by_reference)(struct DtwTree *self, struct DtwTreePart *tree_part);
    void(*add_path_from_hardware)(struct DtwTree *self, char *full_path,bool load_content, bool preserve_content);
    void (*delete_tree)(struct DtwTree *self);
    void(*represent)(struct DtwTree *self);
};

void private_dtw_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part);
void private_dtw_add_tree_part_reference(struct DtwTree *self, struct DtwTreePart *tree_part);
void private_dtw_delete_tree(struct DtwTree *self);
void private_dtw_represent_tree(struct DtwTree *self);
void private_dtw_add_path_from_hardware(struct DtwTree *self, char *full_path,bool load_content, bool preserve_content);

struct  DtwTree * dtw_tree_constructor();

