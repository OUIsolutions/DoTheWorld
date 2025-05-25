#include "doTheWorldOne.c"
#include "src/namespace/randonizer_module/fdeclare.randonizer_module.h"  // Include the necessary header for DtwRandonizerModule

int main() {
    DtwRandonizerModule randonizer = newDtwRandonizerModule();  // Directly use the module
    DtwRandonizer *random = randonizer.newRandonizer();  // Use the function from the module
    char *value1 = randonizer.generate_token(random, 30);  // Use the function from the module
    char *value2 = randonizer.generate_token(random, 30);  // Use the function from the module

    printf("value1 %s\n", value1);
    printf("value2 %s\n", value2);
    randonizer.free(random);  // Use the free function from the module
    // Note: If DtwRandonizerModule itself needs freeing, it should be handled based on its implementation, but it's not shown here.
    return 0;  // Added for completeness, assuming standard main function
}