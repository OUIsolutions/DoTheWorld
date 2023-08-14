
typedef struct DtwStringArray {
  int size;

  char **strings;



}DtwStringArray;

// End the structure with a semicolon
int  DtwStringArray_find_position(struct DtwStringArray *self, const char *string);
void DtwStringArray_append(struct DtwStringArray *self, const char *string);
void DtwStringArray_merge(struct DtwStringArray *self, struct DtwStringArray *other);
void DtwStringArray_represent(struct DtwStringArray *self);
void DtwStringArray_free(struct DtwStringArray *self);
void DtwStringArray_sort(struct DtwStringArray *self);

void DtwStringArray_set_value(struct DtwStringArray *self, int index, const char *value);

struct DtwStringArray * newDtwStringArray();

