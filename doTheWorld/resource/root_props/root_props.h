

typedef struct {
    DtwTransaction  *transaction;
    DtwRandonizer  *randonizer;
    DtwLocker *locker;

}privateDtwResourceRootProps;

privateDtwResourceRootProps *newDtwResourceRootProps();


void privateDtwResourceRootProps_free(privateDtwResourceRootProps *self);

