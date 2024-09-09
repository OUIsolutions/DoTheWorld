
#include "../unique.declaration_requirements.h"

void private_DtwTreePart_set_last_modification(DtwTreePart *self,long last_modification);

char *DtwTreePart_get_content_string_by_reference( DtwTreePart *self);
unsigned char *DtwTreePart_get_content_binary_by_reference( DtwTreePart *self);
char *DtwTreePart_get_content_sha( DtwTreePart *self);
void DtwTreePart_set_any_content( DtwTreePart *self, unsigned char *content, long content_size, bool is_binary);
void DtwTreePart_set_string_content( DtwTreePart *self, const char *content);
void DtwTreePart_set_binary_content( DtwTreePart *self, unsigned char *content, long content_size);
void DtwTreePart_load_content_from_hardware( DtwTreePart *self);
void DtwTreePart_free_content( DtwTreePart *self);
void DtwTreePart_represent( DtwTreePart *self);

bool DtwTreePart_hardware_remove( DtwTreePart *self,int transaction);
bool DtwTreePart_hardware_write( DtwTreePart *self,int transaction);
bool DtwTreePart_hardware_modify( DtwTreePart *self,int transaction);


bool DtwTreePart_hardware_commit(struct DtwTreePart *self);

void DtwTreePart_free(struct DtwTreePart *self);
struct DtwTreePart * DtwTreePart_self_copy(struct DtwTreePart *self);

struct DtwTreePart * newDtwTreePart(const char *path, DtwTreeProps props);
struct DtwTreePart * newDtwTreePartEmpty(const char *path);
struct DtwTreePart * newDtwTreePartLoading(const char *path);
