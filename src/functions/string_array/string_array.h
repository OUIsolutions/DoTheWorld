#include "../unique.declaration_requirements.h"

// End the structure with a semicolon
int  DtwStringArray_find_position( DtwStringArray *self, const char *string);


void DtwStringArray_append_getting_ownership( DtwStringArray *self, char *string);

void DtwStringArray_append( DtwStringArray *self, const char *string);

void DtwStringArray_pop( DtwStringArray *self, int position);

void DtwStringArray_merge( DtwStringArray *self,  DtwStringArray *other);
void DtwStringArray_represent( DtwStringArray *self);
void DtwStringArray_free( DtwStringArray *self);

int private_dtw_string_cmp(const void *a, const void *b);
void DtwStringArray_sort( DtwStringArray *self);

void DtwStringArray_set_value( DtwStringArray *self, int index, const char *value);

 DtwStringArray * newDtwStringArray();

char * privateDtwStringArray_append_if_not_included(DtwStringArray *self,char *value);

DtwStringArray * DtwStringArray_clone(DtwStringArray *self);
