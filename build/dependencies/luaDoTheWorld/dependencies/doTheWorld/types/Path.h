#include "StringArray.h"
#ifndef PRIVATE_DTW_PATH_TYPE_H
#define PRIVATE_DTW_PATH_TYPE_H
typedef struct DtwPath {
    char *original_path_string;
    char *path;
    DtwStringArray *garbage;


}DtwPath;
#endif
