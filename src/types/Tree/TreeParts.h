
#include "../Path.h"

#ifndef PRIVATE_DTW_TREE_PART_TYPE_H
#define PRIVATE_DTW_TREE_PART_TYPE_H

typedef struct DtwTreePart{

    DtwPath *path;
    void *owner;
    long content_size;
    long  hardware_content_size;
    bool content_exist_in_hardware;
    bool ignore;
    bool is_binary;
    bool metadata_loaded;
    char *current_sha;
    char * last_modification_in_str;
    long last_modification_time;
    char *hawdware_content_sha;

    unsigned char *content;
    int pending_action;

}DtwTreePart;
#endif
