
#define DTW_NOT_LOAD_CONTENT  false 
#define DTW_LOAD_CONTENT  true
#define DTW_NOT_PRESERVE_CONTENT  false
#define DTW_PRESERVE_CONTENT  true
#define DTW_NOT_MINIFY  false
#define DTW_MINIFY  true
#define DTW_NOT_PRESERVE_PATH_ATRIBUTES  false
#define DTW_PRESERVE_PATH_ATRIBUTES  true
#define DTW_NOT_PRESERVE_HARDWARE_DATA  false
#define DTW_PRESERVE_HARDWARE_DATA  true
#define DTW_NOT_PRESERVE_CONTENT_DATA  false
#define DTW_PRESERVE_CONTENT_DATA  true

struct  DtwTree{
    int size;
    struct DtwTreePart **tree_parts;
    void (*add_tree_part_by_copy)(struct DtwTree *self, struct DtwTreePart *tree_part);
    void (*add_tree_part_by_reference)(struct DtwTree *self, struct DtwTreePart *tree_part);
    void (*add_path_from_hardware)(struct DtwTree *self,const char *path,bool load_content, bool preserve_content);
    void (*loads_json_tree)(struct DtwTree *self,const char *content);
    char *(*dumps_json_tree)(struct DtwTree *self,bool preserve_content,bool preserve_path_atributes,bool preserve_hadware_data,bool preserve_content_data,bool minify); 
    void (*delete_tree)(struct DtwTree *self);
    void (*represent)(struct DtwTree *self);
};

void private_dtw_add_tree_part_copy(struct DtwTree *self, struct DtwTreePart *tree_part);
void private_dtw_add_tree_part_reference(struct DtwTree *self, struct DtwTreePart *tree_part);
void private_dtw_delete_tree(struct DtwTree *self);
void private_dtw_represent_tree(struct DtwTree *self);
void private_dtw_add_path_from_hardware(struct DtwTree *self,const char *path,bool load_content, bool preserve_content);
void private_dtw_loads_json_tree(struct DtwTree *self,const char *content);
#ifdef __cplusplus
char * private_dtw_dumps_tree_json(
    struct DtwTree *self,
    bool preserve_content=true,
    bool preserve_path_atributes=true,
    bool preserve_hadware_data=false,
    bool preserve_content_data=true,
    bool minify=false);
#else 
char * private_dtw_dumps_tree_json(struct DtwTree *self,bool preserve_content,bool preserve_path_atributes,bool preserve_hadware_data,bool preserve_content_data,bool minify);
#endif
struct  DtwTree * dtw_tree_constructor();

