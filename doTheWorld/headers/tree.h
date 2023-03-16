
struct  DtwTree{
    int size;
    struct DtwTreePart **tree_parts;
    void (*add_tree_part_by_copy)(struct DtwTree *self, struct DtwTreePart *tree_part);
    void (*add_tree_part_by_reference)(struct DtwTree *self, struct DtwTreePart *tree_part);
    void (*add_path_from_hardware)(struct DtwTree *self,const char *path,bool load_content, bool preserve_content);
    char *(*dumps_tree_json)(struct DtwTree *self,bool preserve_content,bool preserve_path_atributes,bool preserve_hadware_data,bool generate_content_sha256,bool minify);
    void (*delete_tree)(struct DtwTree *self);
    void (*represent)(struct DtwTree *self);
};

void private_dtw_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part);
void private_dtw_add_tree_part_reference(struct DtwTree *self, struct DtwTreePart *tree_part);
void private_dtw_delete_tree(struct DtwTree *self);
void private_dtw_represent_tree(struct DtwTree *self);
void private_dtw_add_path_from_hardware(struct DtwTree *self,const char *path,bool load_content, bool preserve_content);
char * private_dtw_dumps_tree_json(struct DtwTree *self,bool preserve_content,bool preserve_path_atributes,bool preserve_hadware_data,bool generate_content_sha256,bool minify);
struct  DtwTree * dtw_tree_constructor();

