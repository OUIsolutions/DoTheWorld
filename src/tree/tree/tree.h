


typedef struct  DtwTree{
    int size;
    struct DtwTreePart **tree_parts;


}DtwTree;


struct DtwTree *DtwTree_get_sub_tree(
    struct DtwTree *self,
    const char *path,
    bool copy_content
);

struct DtwTreePart *DtwTree_find_tree_part_by_function(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part)
        );

struct DtwTree *DtwTree_map(
        struct DtwTree *self,
        struct  DtwTreePart* (*caller)(struct  DtwTreePart *part)
);

struct DtwTree *DtwTree_filter(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part)
);


struct DtwTreePart *DtwTree_find_tree_part_by_name(struct DtwTree *self, const char *name);
struct DtwTreePart *DtwTree_find_tree_part_by_path(struct DtwTree *self, const char *path);

//listages
struct DtwStringArray *DtwTree_list_files(struct DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_dirs(struct DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_all(struct DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_files_recursively(struct DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_dirs_recursively(struct DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_all_recursively(struct DtwTree *self, const char *path,bool concat_path);


void DtwTree_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part);
void DtwTree_remove_tree_part(struct DtwTree *self, int position);
void DtwTree_add_tree_part_by_reference(struct DtwTree *self, struct DtwTreePart *tree_part);
void DtwTree_free(struct DtwTree *self);
void DtwTree_represent(struct DtwTree *self);

void DtwTree_add_tree_parts_from_string_array(
    struct DtwTree *self,
    struct DtwStringArray *paths,
    DtwTreeProps *props
);

void DtwTree_add_tree_from_hardware(
    struct DtwTree *self,
    const char *path,
    DtwTreeProps *props
);

struct DtwTreeTransactionReport * DtwTree_create_report(struct DtwTree *self);



void DtwTree_insecure_hardware_remove_tree(struct DtwTree *self);

void DtwTree_insecure_hardware_write_tree(struct DtwTree *self);

void DtwTree_hardware_commit_tree(struct DtwTree *self);

void DtwTree_loads_json_tree(struct DtwTree *self, const char *content);

void DtwTree_loads_json_tree_from_file(struct DtwTree *self, const char *path);

char * DtwTree_dumps_tree_json(
        struct DtwTree *self,
        DtwTreeProps * props
    );

void DtwTree_dumps_tree_json_to_file(
        struct DtwTree *self,
        const char *path,
        DtwTreeProps * props
    );

struct  DtwTree * newDtwTree();

