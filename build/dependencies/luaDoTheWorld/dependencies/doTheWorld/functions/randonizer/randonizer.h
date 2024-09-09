
#include "../unique.declaration_requirements.h"




DtwRandonizer * newDtwRandonizer();

int DtwRandonizer_generate_num(DtwRandonizer *self,int max);

char * DtwRandonizer_generate_token(struct DtwRandonizer*self, int size);
void DtwRandonizer_free(struct DtwRandonizer *self);
