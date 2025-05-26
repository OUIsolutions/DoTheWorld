### Randonizer
Randonizer it's a way to generate random values, integers or strings

### Numerical Random
```c
#include "doTheWorldOne.c"

int main() {
    DtwRandonizer *random = newDtwRandonizer();
    int value = DtwRandonizer_generate_num(random, 40);
    int value2 = DtwRandonizer_generate_num(random, 40);

    printf("value %d\n", value);
    printf("value2 %d\n", value2);

    DtwRandonizer_free(random);
}
```

### Token Random
```c
#include "doTheWorldOne.c"

int main() {
    DtwRandonizer *random = newDtwRandonizer();
    char *value1 = DtwRandonizer_generate_token(random, 30);
    char *value2 = DtwRandonizer_generate_token(random, 30);

    printf("value1 %s\n", value1);
    printf("value2 %s\n", value2);
    free(value1);
    free(value2);
    DtwRandonizer_free(random);
}
```
