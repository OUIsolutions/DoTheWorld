#include "doTheWorldOne.c"

int main() {
    DtwHash *my_hash = newDtwHash();

    DtwHash_digest_file(my_hash, "tests/target/a.txt");

    printf("after a file: %s\n", my_hash->hash);

    DtwHash_digest_folder_by_content(my_hash, "tests/target");

    printf("after a folder: %s\n", my_hash->hash);

    DtwHash_free(my_hash);
}