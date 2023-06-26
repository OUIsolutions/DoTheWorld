


typedef struct DtwRandonizer{
    long seed;
    long actual_generation;
    char * (*generate_token)(struct DtwRandonizer*self, int size);
}DtwRandonizer;


DtwRandonizer * newDtwRandonizer();
char * DtwRandonizer_generate_token(struct DtwRandonizer*self, int size);



