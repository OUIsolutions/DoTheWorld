
typedef struct DtwHashModule{
    DtwHash * (*newHash)();
    void  (*digest_any)(DtwHash *self,unsigned char *content,long size);
    void (*digest_string)(DtwHash * self, const char *content);
    void  (*digest_file)(DtwHash * self, const char *path);
    void  (*digest_entity_last_modification)(DtwHash * self, const char *path);
    void (*digest_string_array)(DtwHash *self,DtwStringArray *element);
    void (*digest_string_array_last_modifications)(DtwHash *self,DtwStringArray *element);
    void (*digest_string_array_last_modifications_adding_name)(DtwHash *self,DtwStringArray *element);
    void (*digest_string_array_content)(DtwHash *self,DtwStringArray *element);
    void (*digest_string_array_content_adding_name)(DtwHash *self,DtwStringArray *element);
    void (*digest_folder_by_last_modification)(DtwHash *self,const char *path);
    void (*digest_folder_by_content)(DtwHash *self,const char *path);
    void  (*free)(DtwHash *self);

}DtwHashModule;

DtwHashModule newDtwHashModule();