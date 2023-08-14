//
// Created by mateusmoutinho on 05/08/23.
//


void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size){

    if(self->allow_transaction){
        DtwTransaction_write_any(self->transaction,self->path,element,size,true);
    }
    else{
        dtw_write_any_content(self->path,element,size);
    }


}

void DtwResource_set_string(DtwResource *self,const  char *element){
    if(self->allow_transaction){
        DtwTransaction_write_string(self->transaction,self->path,element);
    }
    else{
        dtw_write_string_file_content(self->path,element);
    }

}

void DtwResource_set_long(DtwResource *self,long element){
    if(self->allow_transaction){
        DtwTransaction_write_long(self->transaction,self->path,element);
    }
    else{
        dtw_write_long_file_content(self->path,element);
    }


}

void DtwResource_set_double(DtwResource *self,double element){

    if(self->allow_transaction){
        DtwTransaction_write_double(self->transaction,self->path,element);
    }
    else{
        dtw_write_double_file_content(self->path,element);
    }
}

void DtwResource_set_bool( DtwResource *self,bool element){

    if(self->allow_transaction){
        DtwTransaction_write_bool(self->transaction,self->path,element);
    }
    else{
        dtw_write_bool_file_content(self->path,element);
    }
}
