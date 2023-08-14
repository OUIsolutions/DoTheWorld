
typedef struct DtwTreeModule{

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
            DtwTreeProps *props
    );

    struct DtwTree *(*get_sub_tree)(
            struct DtwTree *self,
            const char *path,
            bool copy_content
    );

    void (*add_tree_from_hardware)(
            struct DtwTree *self,
            const char *path,
            DtwTreeProps *props
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

    DtwStringArray * (*list_files)(struct DtwTree *self, const char *path,bool concat_path);
    DtwStringArray * (*list_dirs)(struct DtwTree *self, const char *path,bool concat_path);
    DtwStringArray * (*list_all)(struct DtwTree *self, const char *path,bool concat_path);

    DtwStringArray * (*list_files_recursively)(struct DtwTree *self, const char *path,bool concat_path);
    DtwStringArray * (*list_dirs_recursively)(struct DtwTree *self, const char *path,bool concat_path);
    DtwStringArray * (*list_all_recursively)(struct DtwTree *self, const char *path,bool concat_path);

    struct DtwTree *(*map)(
            struct DtwTree *self,
            struct  DtwTreePart*(*caller)(struct  DtwTreePart *part)
    );

    struct DtwTreePart *(*find_part_by_name)( struct DtwTree *self,const char *name);
    struct DtwTreePart *(*find_part_by_path)(   struct DtwTree *self,const char *path);


    struct DtwTreeTransactionReport * (*report)(struct DtwTree *self);

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
            DtwTreeProps * props
    );

    void (*dumps_json_tree_to_file)(
            struct DtwTree *self,
            const char *path,
            DtwTreeProps * props
    );

    void (*free)(struct DtwTree *self);
    void (*represent)(struct DtwTree *self);
    void (*insecure_hardware_remove_tree)(struct DtwTree *self);
    void (*insecure_hardware_write_tree)(struct DtwTree *self);
    void (*hardware_commit_tree)(struct DtwTree *self);

}DtwTreeModule;

DtwTreeModule newDtwTreeModule();