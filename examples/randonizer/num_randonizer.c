#include "doTheWorldOne.c"

int main() {
    DtwRandonizer *random = newDtwRandonizer();
    int value = DtwRandonizer_generate_num(random, 40);
    int value2 = DtwRandonizer_generate_num(random, 40);
    
    printf("value %d\n", value);  // Fixed typo in format string
    printf("value2 %d\n", value2);
    
    DtwRandonizer_free(random);
    return 0;  // Added for good practice, though not in original
}