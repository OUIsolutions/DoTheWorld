


typedef struct  DtwTree{
    int size;
    struct DtwTreePart **tree_parts;

    void (*add_tree_part_by_copy)(
        struct DtwTree *self,
         struct DtwTreePart *tree_part
    );

    void (*remove_tree_part)(
            struct DtwTree *self,
            int position
    );

    void (*add_tree_part_by_reference)(
        struct DtwTree *self,
        struct DtwTreePart *tree_part
    );
    void (*add_tree_parts_from_string_array)(
        struct DtwTree *self,
        struct DtwStringArray *paths,
        bool load_metadata,
        bool preserve_content
    );
    
    struct DtwTree *(*get_sub_tree)(
        struct DtwTree *self,
        const char *path,
        bool copy_content
    );

    void (*add_tree_from_hardware)(
        struct DtwTree *self,
        const char *path,
        bool load_content,
        bool load_metadata,
        bool preserve_path_start
    );
    //Listage Functions

    struct DtwTreePart *(*find_part_by_function)(
            struct DtwTree *self,
            bool (*caller)(struct  DtwTreePart *part)
                    );

    struct DtwTree *(*filter)(
            struct DtwTree *self,
            bool (*caller)(struct  DtwTreePart *part)
    );

    struct DtwTree *(*map)(
            struct DtwTree *self,
            struct  DtwTreePart*(*caller)(struct  DtwTreePart *part)
    );

    struct DtwTreePart *(*find_part_by_name)( struct DtwTree *self,const char *name);
    struct DtwTreePart *(*find_part_by_path)(   struct DtwTree *self,const char *path);


    struct DtwTransactionReport * (*report)(struct DtwTree *self);    
    //{%if not  lite %}

    void (*loads_json_tree)(
        struct DtwTree *self,
        const char *content
    );


    void (*loads_json_tree_from_file)(
        struct DtwTree *self,
        const char *path
    );

    char *(*dumps_json_tree)(
            struct DtwTree *self,
            DtwJsonTreeProps * props
    );
    
    void (*dumps_json_tree_to_file)(
            struct DtwTree *self,
            const char *path,
            DtwJsonTreeProps * props
    );

    void (*free)(struct DtwTree *self);
    void (*represent)(struct DtwTree *self);
    void (*insecure_hardware_remove_tree)(struct DtwTree *self);
    void (*insecure_hardware_write_tree)(struct DtwTree *self);
    void (*hardware_commit_tree)(struct DtwTree *self);
}DtwTree;


struct DtwTree *DtwTree_get_sub_tree(
    struct DtwTree *self,
    const char *path,
    bool copy_content
);

struct DtwTreePart *DtwTree_find_by_function(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part)
        );

struct DtwTree *DtwTree_dtw_map(
        struct DtwTree *self,
        struct  DtwTreePart* (*caller)(struct  DtwTreePart *part)
);

struct DtwTree *DtwTree_dtw_filter(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part)
);


struct DtwTreePart *DtwTree_find_tree_part_by_name(struct DtwTree *self, const char *name);
struct DtwTreePart *DtwTree_find_tree_part_by_path(struct DtwTree *self, const char *path);

void DtwTree_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part);
void DtwTree_remove_tree_part(struct DtwTree *self, int position);
void DtwTree_add_tree_part_reference(struct DtwTree *self, struct DtwTreePart *tree_part);
void DtwTree_dtw_free_tree(struct DtwTree *self);
void DtwTree_represent_tree(struct DtwTree *self);

void DtwTree_add_tree_parts_from_string_array(
    struct DtwTree *self,
    struct DtwStringArray *paths,
    bool load_content,
    bool load_metadata
);

void DtwTree_add_tree_from_hardware(
    struct DtwTree *self,
    const char *path,
    bool load_content,
    bool load_meta_data,
    bool preserve_path_start
);

struct DtwTransactionReport * DtwTree_create_report(struct DtwTree *self);


void DtwTree_insecure_hardware_remove_tree(struct DtwTree *self);
void DtwTree_insecure_hardware_write_tree(struct DtwTree *self);
void DtwTree_hardware_commit_tree(struct DtwTree *self);


void DtwTree_loads_json_tree(struct DtwTree *self, const char *content);
void DtwTree_loads_json_tree_from_file(struct DtwTree *self, const char *path);

char * DtwTree_dumps_tree_json(
        struct DtwTree *self,
        DtwJsonTreeProps * props
    );

void DtwTree_dumps_tree_json_to_file(
        struct DtwTree *self,
        const char *path,
        DtwJsonTreeProps * props
    );

struct  DtwTree * newDtwTree();
