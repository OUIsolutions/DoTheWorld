#include "Action.h"

#ifndef PRIVATE_DT_TRANSACTION_TYPE_H
#define PRIVATE_DT_TRANSACTION_TYPE_H

typedef struct DtwTransaction{

    DtwActionTransaction  **actions;
    long size;

}DtwTransaction;
#endif
