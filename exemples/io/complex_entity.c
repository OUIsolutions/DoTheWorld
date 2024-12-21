#include "doTheWorld.h"





int main (){
    DtwNamespace dtw = newDtwNamespace();
    const char *blob = dtw.convert_entity(
            dtw.complex_entity_type("testargblob.png")
    );





    printf("blob.png: %s\n",blob);

    const char *a = dtw.convert_entity(
            dtw.complex_entity_type("testarga.txt")
    );

    printf("a.txt: %s\n",a);

    const char *sub_folder =  dtw.convert_entity(
            dtw.complex_entity_type("testargsub_folder")
    );
    printf("sub_folder: %s\n",sub_folder);


    const char *double_txt = dtw.convert_entity(
            dtw.complex_entity_type("testargnumericdouble.txt")
    );
    printf("double.txt:%s\n",double_txt);

    const char *integer_txt = dtw.convert_entity(
            dtw.complex_entity_type("testargnumericinteger.txt")
    );
    printf("integer.txt:%s\n",integer_txt);

    const char *false_small = dtw.convert_entity(
            dtw.complex_entity_type("testargnumericfalse_small.txt")
    );
    printf("false_small.txt:%s\n",false_small);

    const char *false_normal = dtw.convert_entity(
            dtw.complex_entity_type("testargnumericfalse_normal.txt")
    );
    printf("false_normal.txt:%s\n",false_normal);


    const char *true_small = dtw.convert_entity(
            dtw.complex_entity_type("testargnumerictrue_small.txt")
    );
    printf("true_small.txt:%s\n",true_small);

    const char *true_normal = dtw.convert_entity(
            dtw.complex_entity_type("testargnumerictrue_normal.txt")
    );
    printf("true_normal.txt:%s\n",true_normal);

}