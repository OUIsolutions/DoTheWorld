


typedef struct DtwRandonizer{
    long seed;
    long actual_generation;

}DtwRandonizer;


DtwRandonizer * newDtwRandonizer();
char * DtwRandonizer_generate_token(struct DtwRandonizer*self, int size);
void DtwRandonizer_free(struct DtwRandonizer *self);


