

DtwResource * DtwResource_append(DtwResource *self){
    long  size = dtw_get_total_itens_of_dir(self->path);
    if(size < 0){
        size = 0;
    }
    while(true){

        char path[20] ={0};
        sprintf(path,"%ld",size);
        DtwResource *new_element = DtwResource_sub_resource_ensuring_not_exist(self,path);
        if(new_element){
            return new_element;
        }
        size++;
    }


}
/*
DtwResource * DtwResource_now(DtwResource *self);

DtwResource * DtwResource_now_in_unix(DtwResource *self);

DtwResource * DtwResource_random(DtwResource *self);
*/