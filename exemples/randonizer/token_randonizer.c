
#include "doTheWorld.h"


int main() {
    DtwNamespace dtw = newDtwNamespace();
    DtwRandonizer *random = dtw.randonizer.newRandonizer();
    char *value1 = dtw.randonizer.generate_token(random,30);
    char *value2 = dtw.randonizer.generate_token(random,30);

    printf("value1 %s\n",value1);

    printf("value2 %s\n",value2);
    free(value1);
    free(value2);
    dtw.randonizer.free(random);
}