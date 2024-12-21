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
