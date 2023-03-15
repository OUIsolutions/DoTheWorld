
struct DtwTreePart{
    
    struct DtwPath *path;
    bool content_exist_in_memory;
    long last_modification_time;
    bool content_exist_in_hardware;
    bool ignore;
    bool is_binary;
    char *hawdware_content_sha;
    char *content;

    int content_size;

    char *(*get_content_sha)(struct DtwTreePart *self);
    char *(*last_modification_time_in_string)(struct DtwTreePart *self);
    void (*set_any_content)(struct DtwTreePart *self,const char *content,int content_size,bool is_binary,bool set_last_modification_time);
    void (*set_string_content)(struct DtwTreePart *self,const char *content);
    void (*set_binary_content)(struct DtwTreePart *self,const char *content,int content_size);
    void (*load_content_from_hardware)(struct DtwTreePart *self);
    void (*free_content)(struct DtwTreePart *self);
    void(*represent)(struct DtwTreePart *self);
    bool(*hardware_remove)(struct DtwTreePart *self);
    bool(*hardware_write)(struct DtwTreePart *self);
    void (*delete_tree_part)(struct DtwTreePart *self);
    struct DtwTreePart *(*copy_tree_part)(struct DtwTreePart *self);
};
char *private_dtw_get_content_sha(struct DtwTreePart *self);
char *private_dtw_last_modification_time_in_string(struct DtwTreePart *self);
void private_dtw_set_any_content(struct DtwTreePart *self,const char *content,int content_size,bool is_binary,bool set_last_modification_time);
void private_dtw_set_string_content(struct DtwTreePart *self,const char *content);
void private_dtw_set_binary_content(struct DtwTreePart *self,const char *content,int content_size);
void private_dtw_load_content_from_hardware(struct DtwTreePart *self);
void private_dtw_free_content(struct DtwTreePart *self);
void private_dtw_represent_tree_part(struct DtwTreePart *self);
bool private_dtw_hardware_remove(struct DtwTreePart *self);
bool private_dtw_hardware_write(struct DtwTreePart *self);
void private_dtw_tree_part_destructor(struct DtwTreePart *self);
struct DtwTreePart * private_dtw_copy_tree(struct DtwTreePart *self);



struct DtwTreePart * dtw_tree_part_constructor(const char *full_path,bool load_content);