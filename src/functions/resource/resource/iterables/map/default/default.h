#include "../unique.declaration_requirements.h"

int  private_dtwResource_compare(const void *item1,const void*item2);


void DtwResource_map(
DtwResource *self,
void *main_array,
void(*append)(void *main_array_arg, void *item),
bool(*filtrage_callback)(DtwResource *item, void *args),
int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args),
void *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd
);

void DtwResource_schema_map(
DtwResource *self,
void *main_array,
void(*append)(void *main_array_arg, void *item),
bool(*filtrage_callback)(DtwResource *item, void *args),
int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args),
void *(*callback)(DtwResource *item, void *args),
void *args,
int start,
int qtd
);
