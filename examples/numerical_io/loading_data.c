
#include "doTheWorldOne.c"




int main (){

    DtwNamespace dtw = newDtwNamespace();

    double double_txt = dtw.load_double_file_content("tests/target/numerical/double.txt");
    printf("double.txt:%lf\n",double_txt);

    double double_that_not_exist = dtw.load_double_file_content("nothing.txt");
    printf("double that not exist:%lf\n",double_that_not_exist);


    long integer_txt = dtw.load_long_file_content("tests/target/numerical/integer.txt");
    printf("integer.txt:%ld\n",integer_txt);


    long integer_that_not_exist = dtw.load_long_file_content("nothing.txt");
    printf("integer that not exist:%ld\n",integer_that_not_exist);

    //false_small.txt = "f"
    bool false_small = dtw.load_bool_file_content("tests/target/numerical/false_small.txt");
    printf("false_small.txt:%d\n",false_small);

    //false_normal.txt = "false"
    bool false_normal = dtw.load_bool_file_content("tests/target/numerical/false_normal.txt");
    printf("false_normal.txt:%d\n",false_normal);

    //true_small.txt = "t"
    bool true_small = dtw.load_bool_file_content("tests/target/numerical/true_small.txt");
    printf("true_small.txt:%d\n",true_small);

    //true normal.txt = "true"
    bool true_normal = dtw.load_bool_file_content("tests/target/numerical/true_normal.txt");
    printf("true_normal.txt:%d\n",true_normal);

    bool bool_that_not_exist = dtw.load_bool_file_content("nothing.txt");
    printf("false that not exist:%d\n",bool_that_not_exist);

    return 0;

}
