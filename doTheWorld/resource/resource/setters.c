//
// Created by mateusmoutinho on 05/08/23.
//


void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size){
    char *path = private_DtwResource_get_path(self);

    if(self->allow_transaction){
        self->transaction->write_any(self->transaction,path,element,size,true);
    }
    else{
        dtw_write_any_content(path,element,size);
    }

    free(path);

}

void DtwResource_set_string(DtwResource *self,const  char *element){
    char *path = private_DtwResource_get_path(self);
    if(self->allow_transaction){
        self->transaction->write_string(self->transaction,path,element);
    }
    else{
        dtw_write_string_file_content(path,element);
    }
    free(path);

}

void DtwResource_set_long(DtwResource *self,long element){
    char *path = private_DtwResource_get_path(self);
    if(self->allow_transaction){
        self->transaction->write_long(self->transaction,path,element);
    }
    else{
        dtw_write_long_file_content(path,element);
    }
    free(path);

}

void DtwResource_set_double(DtwResource *self,double element){
    char *path = private_DtwResource_get_path(self);

    if(self->allow_transaction){
        self->transaction->write_double(self->transaction,path,element);
    }
    else{
        dtw_write_double_file_content(path,element);
    }
    free(path);
}

void DtwResource_set_bool( DtwResource *self,bool element){
    char *path = private_DtwResource_get_path(self);

    if(self->allow_transaction){
        self->transaction->write_bool(self->transaction,path,element);
    }
    else{
        dtw_write_bool_file_content(path,element);
    }
    free(path);
}
