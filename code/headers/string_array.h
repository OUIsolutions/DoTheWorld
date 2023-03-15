
struct DtwStringArray {
  int size;         

  char **strings;       
  void (*set_value)(struct DtwStringArray *self,int index,const char *value);
  void (*add_string)(struct DtwStringArray *self,const char *string);
  void (*merge_string_array)(struct DtwStringArray *self, struct DtwStringArray *other);
  void (*represent)(struct DtwStringArray *self);
  void (*delete_string_array)(struct DtwStringArray *self);
}; // End the structure with a semicolon

void private_dtw_add_string(struct DtwStringArray *self,const char *string);
void private_dtw_merge_string_array(struct DtwStringArray *self, struct DtwStringArray *other);
void private_dtw_represent_string_array(struct DtwStringArray *self);
void private_dtw_delete_string_array(struct DtwStringArray *self);
void private_dtw_set_value(struct DtwStringArray *self,int index,const char *value);

struct DtwStringArray * dtw_constructor_string_array();
