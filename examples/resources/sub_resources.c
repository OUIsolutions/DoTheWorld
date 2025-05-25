#include "doTheWorldOne.c"

int main() {
    DtwResource *values = new_DtwResource("tests/target");
    DtwResourceArray *listage = DtwResource_sub_resources(values);

    for(int i = 0; i < listage->size; i++) {
        DtwResource *current = listage->resources[i];
        printf("----------------------------------------\n");
        DtwResource_represent(current);
    }

    DtwResource_free(values);
}