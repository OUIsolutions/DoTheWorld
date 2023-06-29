
typedef struct DtwStringArray {
  int size;

  char **strings;
  bool *ownership;
  
  void (*set_value)(struct DtwStringArray *self,int index,const char *value);
  void (*add_string)(struct DtwStringArray *self,const char *string);
  void (*merge_string_array)(struct DtwStringArray *self, struct DtwStringArray *other);
  void (*represent)(struct DtwStringArray *self);
  void (*free)(struct DtwStringArray *self);
  int (*find_position)(struct DtwStringArray *self,const char *string);

}DtwStringArray;

// End the structure with a semicolon
int  DtwStringArray_dtw_find_position(struct DtwStringArray *self, const char *string);
void DtwStringArray_dtw_add_string(struct DtwStringArray *self, const char *string);
void DtwStringArray_dtw_merge_string_array(struct DtwStringArray *self, struct DtwStringArray *other);
void DtwStringArray_dtw_represent_string_array(struct DtwStringArray *self);
void DtwStringArray_dtw_free_string_array(struct DtwStringArray *self);
void DtwStringArray_dtw_set_value(struct DtwStringArray *self, int index, const char *value);

struct DtwStringArray * newDtwStringArray();
