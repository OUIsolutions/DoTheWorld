

typedef  struct DtwHash{
    char *hash;
}DtwHash;


DtwHash * newDtwHash();

void  DtwHash_digest_any(DtwHash *self,unsigned char *content,long size);

void DtwHash_digest_string(DtwHash * self, const char *content);

void  DtwHash_digest_file(DtwHash * self, const char *path);

void  DtwHash_digest_last_modification(DtwHash * self, const char *path);


void DtwHash_digest_string_array(DtwHash *self,DtwStringArray *element);

void DtwHash_digest_string_array_last_modifications(DtwHash *self,DtwStringArray *element);

void DtwHash_digest_string_array_content(DtwHash *self,DtwStringArray *element);

void  DtwHash_free(DtwHash *self);

