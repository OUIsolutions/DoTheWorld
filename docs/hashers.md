
## Sha256
Generating Sha from file

```c

#include "doTheWorld.h"

int main(int argc, char *argv[]){
    DtwNamespace dtw = newDtwNamespace();

   char *hash = dtw.generate_sha_from_file("tests/target/blob.png");
   printf("SHA: %s", hash);
   free(hash);
}

```




### Hash

By using hash Object you can digest values,( its very usefull in dynamic programing)
or to avoid recomputation in compilers or bundlers

### Simple Hashing

```c
#include "doTheWorld.h"





int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwHash *my_hash = dtw.hash.newHash();

    dtw.hash.digest_string(my_hash,"my string");
    printf("value after digest string %s\n",my_hash->hash);

    dtw.hash.digest_long(my_hash,10);
    printf("value after long: %s\n",my_hash->hash);

    dtw.hash.digest_double(my_hash,15.6);
    printf("value after double: %s\n",my_hash->hash);

    dtw.hash.digest_bool(my_hash,true);
    printf("value after digest bool %s\n",my_hash->hash);

    DtwStringArray *test = dtw.string_array.newStringArray();
    dtw.string_array.append(test,"b");
    dtw.string_array.append(test,"a");

    dtw.hash.digest_string_array(my_hash,test);
    printf("value after string array %s\n",my_hash->hash);
    dtw.string_array.free(test);

    dtw.hash.free(my_hash);
}

```

```c
#include "doTheWorld.h"





int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwHash *my_hash = dtw.hash.newHash();

    dtw.hash.digest_file(my_hash,"tests/target/a.txt");

    printf("after a file :%s\n",my_hash->hash);

    dtw.hash.digest_folder_by_content(my_hash,"tests/target");
    printf("after a folder %s\n",my_hash->hash);

    dtw.hash.free(my_hash);
}

```

```c
#include "doTheWorld.h"





int main (){
    DtwNamespace dtw = newDtwNamespace();

    DtwHash *my_hash = dtw.hash.newHash();

    dtw.hash.digest_entity_last_modification(my_hash,"tests/target/a.txt");

    printf("after a file :%s\n",my_hash->hash);

    dtw.hash.digest_folder_by_last_modification(my_hash,"tests/target");
    printf("after a folder %s\n",my_hash->hash);

    dtw.hash.free(my_hash);
}

```

