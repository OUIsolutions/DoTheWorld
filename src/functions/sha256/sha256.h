#include "../unique.declaration_requirements.h"

char * calc_sha_256_returning_string(const void *input, size_t len);

void calc_sha_256_from_string(uint8_t hash[SIZE_OF_SHA_256_HASH], const char *input);

int calc_sha_256_from_file(uint8_t hash[SIZE_OF_SHA_256_HASH], const char *filename);

char * calc_sha_256_from_string_returning_string(const char *input);

char * calc_sha_256_from_file_returning_string(const char *filename);

char * sha256_open_file(const char *filename, int *size);
