
//listages
struct DtwStringArray *DtwTree_list_files(struct DtwTree *self, const char *path,bool concat_path){
    DtwStringArray *formated_elements = newDtwStringArray();
    for(int i = 0; i < self->size; i++){
       DtwTreePart *current = self->tree_parts[i];
       DtwPath *current_path = current->path;
       char *current_path_string = current_path->get_path(current_path);
       if(dtw_starts_with(current_path,path)){
           formated_elements->append(current_path_string);
           free(current_path_string);
       }
    }
    return formated_elements;
}

struct DtwStringArray *DtwTree_list_dirs(struct DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_all(struct DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_files_recursively(struct DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_dirs_recursively(struct DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_all_recursively(struct DtwTree *self, const char *path,bool concat_path);

