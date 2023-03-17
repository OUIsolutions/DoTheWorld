
#define DTW_IS_BINARY true
#define DTW_IS_NOT_BINARY false
struct DtwTreePart{
    
    struct DtwPath *path;
    bool content_exist_in_memory;
    int  hardware_content_size; 
    long last_modification_time;
    bool content_exist_in_hardware;
    bool ignore;
    bool is_binary;
    char *hawdware_content_sha;
    char *content;

    int content_size;

    char *(*get_content_sha)(struct DtwTreePart *self);
    char *(*last_modification_time_in_string)(struct DtwTreePart *self);
    void (*set_any_content)(struct DtwTreePart *self,const char *content,int content_size,bool is_binary);
    void (*set_string_content)(struct DtwTreePart *self,const char *content);
    void (*set_binary_content)(struct DtwTreePart *self,const char *content,int content_size);
    void (*load_content_from_hardware)(struct DtwTreePart *self);
    void (*free_content)(struct DtwTreePart *self);
    void(*represent)(struct DtwTreePart *self);
    
    bool(*hardware_remove)(struct DtwTreePart *self);
    bool(*hardware_write)(struct DtwTreePart *self);
    bool(*hardware_modify)(struct DtwTreePart *self);

    void (*delete_tree_part)(struct DtwTreePart *self);
    struct DtwTreePart *(*copy_tree_part)(struct DtwTreePart *self);
};
char *private_dtw_get_content_sha(struct DtwTreePart *self);
char *private_dtw_last_modification_time_in_string(struct DtwTreePart *self);
void private_dtw_set_any_content(struct DtwTreePart *self,const char *content,int content_size,bool is_binary);
void private_dtw_set_string_content(struct DtwTreePart *self,const char *content);
void private_dtw_set_binary_content(struct DtwTreePart *self,const char *content,int content_size);
void private_dtw_load_content_from_hardware(struct DtwTreePart *self);
void private_dtw_free_content(struct DtwTreePart *self);
void private_dtw_represent_tree_part(struct DtwTreePart *self);
bool private_dtw_hardware_remove(struct DtwTreePart *self);
bool private_dtw_hardware_write(struct DtwTreePart *self);
bool private_dtw_hardware_modify(struct DtwTreePart *self);

void private_dtw_tree_part_destructor(struct DtwTreePart *self);
struct DtwTreePart * private_dtw_copy_tree(struct DtwTreePart *self);

struct DtwTreePart * dtw_tree_part_constructor(const char *path,bool load_content,bool preserve_content);