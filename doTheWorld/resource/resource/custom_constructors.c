

DtwResource * DtwResource_sub_resource_next(DtwResource *self, const char *end_path){
    long  size = dtw_get_total_itens_of_dir(self->path);
    if(size < 0){
        size = 0;
    }
    while(true){

        char path[300] ={0};
        if(end_path){
            sprintf(path,"%ld%s",size,end_path);
        }
        else{
            sprintf(path,"%ld",size);
        }
        DtwResource *new_element = DtwResource_sub_resource_ensuring_not_exist(self,"%s",path);
        if(new_element){
            return new_element;
        }
        size = size+1;
    }
}

/*
DtwResource * DtwResource_now(DtwResource *self){

    while(true){

        char path[300] ={0};
        if(end_path){
            sprintf(path,"%ld%s",size,end_path);
        }
        else{
            sprintf(path,"%ld",size);
        }
        DtwResource *new_element = DtwResource_sub_resource_ensuring_not_exist(self,"%s",path);
        if(new_element){
            return new_element;
        }
        size = size+1;
    }
}

DtwResource * DtwResource_now_in_unix(DtwResource *self);

DtwResource * DtwResource_random(DtwResource *self);
*/