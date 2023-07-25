#include "doTheWorld.h"



int main (){

    char *blob = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/blob.png")
    );

    printf("blob.png: %s\n",blob);

    char *a = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/a.txt")
    );

    printf("a.txt: %s\n",a);

    char *sub_folder =  dtw_convert_entity(
            dtw_complex_entity_type("tests/target/sub_folder")
    );
    printf("sub_folder: %s\n",sub_folder);


    char *double_txt = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/double.txt")
    );
    printf("double.txt:%s\n",double_txt);

    char *integer_txt = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/integer.txt")
    );
    printf("integer.txt:%s\n",integer_txt);

    char *false_small = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/false_small.txt")
    );
    printf("false_small.txt:%s\n",false_small);

    char *false_normal = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/false_normal.txt")
    );
    printf("false_normal.txt:%s\n",false_normal);


    char *true_small = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/true_small.txt")
    );
    printf("true_small.txt:%s\n",true_small);

    char *true_normal = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/true_normal.txt")
    );
    printf("false_normal.txt:%s\n",true_normal);

}