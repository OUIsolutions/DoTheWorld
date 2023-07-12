

typedef struct DtwTransactionAction{
    int action;
    char *source1;
    char *source2;
    char *sha256;
    bool is_binary;
    unsigned char *element;
    long size;

}DtwTransactionAction;


DtwTransactionAction * newDtwTransactionAction(
        int action,
        const char *source1,
        const char *source2,
        const char *sha256,
        bool is_binary,
        unsigned char *element,
        long size
);

char *DtwTransactionAction_convert_action(DtwTransactionAction * self);

int DtwTransactionAction_convert_string(const char *actionString);

void DtwTransactionAction_represent(DtwTransactionAction * self);


void DtwTransactionAction_free(DtwTransactionAction * self);




