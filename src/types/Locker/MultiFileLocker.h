#include "../StringArray.h"
#ifndef PRIVATE_DTW_MULTIFILE_LOCKER_TYPE_H
#define PRIVATE_DTW_MULTIFILE_LOCKER_TYPE_H

typedef struct {

    int total_checks;
    int process;
    int max_wait;
    int max_lock_time;
    DtwStringArray *locked_elements;


}DtwMultiFileLocker;
#endif
