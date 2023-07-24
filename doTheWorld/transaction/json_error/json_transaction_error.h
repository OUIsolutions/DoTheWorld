
typedef struct DtwJsonTransactionError{
    int code;
    char mensage[200];
    char path[30];

}DtwJsonTransactionError;

DtwJsonTransactionError * private_new_DtwJsonTransactionError( int code,const char *mensage,const  char *path);

