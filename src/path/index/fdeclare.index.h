//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.typesm.h"
//silver_chain_scope_end



int DtwPath_get_total_dirs(DtwPath *self);

char *DtwPath_get_sub_dirs_from_index(DtwPath *self, int start, int end);


int private_dtw_count_dirs_before(const char *dirs,int index);

void DtwPath_insert_dir_at_index(DtwPath *self, int index, const char *dir);

void DtwPath_remove_sub_dirs_at_index(DtwPath *self, int start, int end);
