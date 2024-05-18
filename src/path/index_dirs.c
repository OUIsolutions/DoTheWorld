
int DtwPath_get_total_dirs(DtwPath *self){
    int size = 0;
    int path_size = (int)strlen(self->path);
    for(int i = 0; i < path_size;i++){
        char current = self->path[i];
        if(current == '/' || current =='\\'){
            size+=1;
        }
    }
    return size;
}

char *DtwPath_get_sub_dirs(DtwPath *self, int start,int end){

    int size = DtwPath_get_total_dirs(self);
    if(size == 0){
        return NULL;
    }
    int converted_start_index = (int)private_dtw_convert_index(start, size);
    int converted_end_index = (int)private_dtw_convert_index(end, size);

    char *dir = DtwPath_get_dir(self);
    int  dirs_string_size = (int)strlen(dir);
    int total_dirs = 0;
    int start_point = 0;
    int end_point = dirs_string_size;

    for(int i= 0 ;i < dirs_string_size;i++ ){
        char current = dir[i];
        if(current == '/' || current =='\\'){
            total_dirs+=1;
        }
        if(total_dirs == converted_start_index){
            start_point = i;
        }

        if(total_dirs == (converted_end_index + 1)){
            end_point = i;
        }
    }
    char *buffer = private_dtw_sub_str(dir,start_point,end_point);
    return privateDtwStringArray_append_if_not_included(self->garbage,buffer);
}

int private_dtw_count_dirs_after_index(const char *dirs,int index){
    int size = (int)strlen(dirs);
    int converted_point = index;
    for(int i = index; i < size;i++){
        char current_char = dirs[i];
        if(current_char == '\\' || current_char == '/' ){
            converted_point = i;
            break;
        }
    }

    return private_dtw_count_dirs_before(dirs,converted_point);
}


int private_dtw_count_dirs_before(const char *dirs,int index){
    int total = 0;
    for(int i =index; i >=0; i--){
        char current_char = dirs[i];
        if(current_char == '\\' || current_char == '/' ){
            total+=1;
        }
    }
    return  total;
}

void DtwPath_insert_dir_at(DtwPath *self,int index,const char *dir){

    char * starter = DtwPath_get_sub_dirs(self,0,index);
    int size = DtwPath_get_total_dirs(self);
    int converted_index = (int)private_dtw_convert_index(index,size);
    const char *rest ="";
    if(converted_index < size-1){
        rest = DtwPath_get_sub_dirs(self,index+1,-1);
    }

    char *buffer = private_dtw_formatt("%s/%s/%s",starter,dir,rest);
    DtwPath_set_dir(self,buffer);
    free(buffer);
}

void DtwPath_insert_dir_after(DtwPath *self,const char *str,const char *dir){
    char *current_dir = DtwPath_get_dir(self);
    int index = (int)dtw_index_of_string(current_dir,str);
    if(index == -1){
        return;
    }

    int start = private_dtw_count_dirs_before(current_dir,index);
    printf("start %d\n",start);
    DtwPath_insert_dir_at(self,start,dir);
}