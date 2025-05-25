#include "doTheWorldOne.c"

int main() {
    DtwHash *my_hash = newDtwHash();

    DtwHash_digest_string(my_hash, "my string");
    printf("value after digest string %s\n", my_hash->hash);

    DtwHash_digest_long(my_hash, 10);
    printf("value after long: %s\n", my_hash->hash);

    DtwHash_digest_double(my_hash, 15.6);
    printf("value after double: %s\n", my_hash->hash);

    DtwHash_digest_bool(my_hash, true);
    printf("value after digest bool %s\n", my_hash->hash);

    DtwStringArray *test = newDtwStringArray();
    DtwStringArray_append(test, "b");
    DtwStringArray_append(test, "a");

    DtwHash_digest_string_array(my_hash, test);
    printf("value after string array %s\n", my_hash->hash);
    DtwStringArray_free(test);

    DtwHash_free(my_hash);
}