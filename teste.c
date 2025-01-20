
#include "src/one.c"

int main (){
    char *t1 = dtw_concat_path("tests/", "target/a.txt");

    char *contentudo = dtw_load_string_file_content(t1);
    printf("%s\n",contentudo);
    free(t1);
    free(contentudo);
}
