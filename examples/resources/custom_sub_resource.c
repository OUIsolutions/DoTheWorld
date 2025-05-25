#include "doTheWorldOne.c"
#include "src/namespace/resource_module/resource_module/fdeclare.resource_module.h"  // Include the necessary header for DtwResourceModule

int main() {
    DtwResourceModule resource = newDtwResourceModule();  // Initialize the resource module directly
    DtwResource *test = resource.newResource("tests/target");

    DtwResource *next = resource.sub_resource_next(test, ".txt");
    resource.set_string(next, "next-value");

    DtwResource *random = resource.sub_resource_random(test, ".txt");
    resource.set_string(random, "random-value");

    DtwResource *now = resource.sub_resource_now(test, ".txt");
    resource.set_string(now, "now value");

    DtwResource *now_in_unix = resource.sub_resource_now_in_unix(test, ".txt");
    resource.set_string(now_in_unix, "now in unix");

    resource.commit(test);
    resource.free(test);
}