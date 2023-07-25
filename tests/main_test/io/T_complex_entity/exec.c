#include "../../../doTheWorld_test.h"



int main (){

    const char *blob = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/blob.png")
    );

    printf("blob.png: %s\n",blob);

    const char *a = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/a.txt")
    );

    printf("a.txt: %s\n",a);

    const char *sub_folder =  dtw_convert_entity(
            dtw_complex_entity_type("tests/target/sub_folder")
    );
    printf("sub_folder: %s\n",sub_folder);


    const char *double_txt = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/double.txt")
    );
    printf("double.txt:%s\n",double_txt);

    const char *integer_txt = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/integer.txt")
    );
    printf("integer.txt:%s\n",integer_txt);

    const char *false_small = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/false_small.txt")
    );
    printf("false_small.txt:%s\n",false_small);

    const char *false_normal = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/false_normal.txt")
    );
    printf("false_normal.txt:%s\n",false_normal);


    const char *true_small = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/true_small.txt")
    );
    printf("true_small.txt:%s\n",true_small);

    const char *true_normal = dtw_convert_entity(
            dtw_complex_entity_type("tests/target/numerical/true_normal.txt")
    );
    printf("true_normal.txt:%s\n",true_normal);

}