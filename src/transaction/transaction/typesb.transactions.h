

#ifndef PRIVATE_DT_TRANSACTION_TYPE_H
#define PRIVATE_DT_TRANSACTION_TYPE_H

typedef struct DtwTransaction{
    DtwEncriptionInterface *encryption;
    short save_mode;
    DtwActionTransaction  **actions;
    long size;

}DtwTransaction;
#endif
