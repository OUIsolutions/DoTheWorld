
#include "../../../doTheWorld_test.h"


int main() {
    DtwNamespace dtw = newDtwNamespace();
    DtwRandonizer *random = dtw.randonizer.newRandonizer();
    int value = dtw.randonizer.generate_num(random,40);
    int value2 = dtw.randonizer.generate_num(random,40);

    printf("value%d\n",value);

    printf("value2 %d\n",value2);

    dtw.randonizer.free(random);
}