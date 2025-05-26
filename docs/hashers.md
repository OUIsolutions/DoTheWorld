## Sha256
Generating Sha from file

```c

#include "doTheWorldOne.c"

int main(int argc, char *argv[]){
   char *hash = dtw_generate_sha_from_file("tests/target/blob.png");
   printf("SHA: %s", hash);
   free(hash);
}

```



### Hash

By using hash Object you can digest values,( its very usefull in dynamic programing)
or to avoid recomputation in compilers or bundlers

### Simple Hashing

```c
#include "doTheWorldOne.c"




int main (){
    DtwHash *my_hash = newDtwHash();

    DtwHash_digest_string(my_hash,"my string");
    printf("value after digest string %s\n",my_hash->hash);

    DtwHash_digest_long(my_hash,10);
    printf("value after long: %s\n",my_hash->hash);

    DtwHash_digest_double(my_hash,15.6);
    printf("value after double: %s\n",my_hash->hash);

    DtwHash_digest_bool(my_hash,true);
    printf("value after digest bool %s\n",my_hash->hash);

    DtwStringArray *test = newDtwStringArray();
    DtwStringArray_append(test,"b");
    DtwStringArray_append(test,"a");

    DtwHash_digest_string_array(my_hash,test);
    printf("value after string array %s\n",my_hash->hash);
    DtwStringArray_free(test);

    DtwHash_free(my_hash);
}

```

```c
#include "doTheWorldOne.c"




int main (){
    DtwHash *my_hash = newDtwHash();

    DtwHash_digest_file(my_hash,"tests/target/a.txt");

    printf("after a file :%s\n",my_hash->hash);

    DtwHash_digest_folder_by_content(my_hash,"tests/target");
    printf("after a folder %s\n",my_hash->hash);

    DtwHash_free(my_hash);
}

```

```c
#include "doTheWorldOne.c"




int main (){
    DtwHash *my_hash = newDtwHash();

    DtwHash_digest_entity_last_modification(my_hash,"tests/target/a.txt");

    printf("after a file :%s\n",my_hash->hash);

    DtwHash_digest_folder_by_last_modification(my_hash,"tests/target");
    printf("after a folder %s\n",my_hash->hash);

    DtwHash_free(my_hash);
}

```