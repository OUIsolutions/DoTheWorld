

typedef struct DtwTransactionAction{
    int action;
    char *source1;
    char *source2;
    bool is_binary;
    unsigned char *element;
    long size;

}DtwTransactionAction;


DtwTransactionAction * newDtwTransactionAction(
        int action,
        const char *source1,
        const char *source2,
        bool is_binary,
        unsigned char *element,
        long size
);

char *DtwTransactionAction_convert_action(DtwTransactionAction * self);



void DtwTransactionAction_represent(DtwTransactionAction * self);


void DtwTransactionAction_free(DtwTransactionAction * self);




