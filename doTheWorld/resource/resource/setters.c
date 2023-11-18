//
// Created by mateusmoutinho on 05/08/23.
//


void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size){

    if(self->allow_transaction){
        DtwTransaction_write_any(self->root_props->transaction,self->path,element,size,true);
    }
    else{
        dtw_write_any_content(self->path,element,size);
    }
    DtwResource_unload(self);
    self->loaded = true;
    self->value_size = size;
    self->value_any = (unsigned  char *) malloc(size+1);
    memcpy(self->value_any,element,size);

}



void DtwResource_set_string(DtwResource *self,const  char *element){
    if(self->allow_transaction){
        DtwTransaction_write_string(self->root_props->transaction,self->path,element);
    }
    else{
        dtw_write_string_file_content(self->path,element);
    }
    DtwResource_unload(self);

    self->loaded = true;

    self->value_size = (long)strlen(element);

    self->value_any = (unsigned char*)strdup(element);


}

void DtwResource_set_binary_in_sub_resource(DtwResource *self, unsigned char *element, long size,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_binary(created,element,size);
}

void DtwResource_set_string_in_sub_resource(DtwResource *self,const  char *element,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_string(created,element);
}




void DtwResource_set_long(DtwResource *self,long element){
    if(self->allow_transaction){
        DtwTransaction_write_long(self->root_props->transaction,self->path,element);
    }
    else{
        dtw_write_long_file_content(self->path,element);
    }
    DtwResource_unload(self);
    self->loaded = true;
    char result[20] ={0};
    sprintf(result,"%ld",element);
    self->value_any = (unsigned char *)strdup(result);

}
void DtwResource_set_long_in_sub_resource(DtwResource *self,long element,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_long(created,element);
}

void DtwResource_set_double(DtwResource *self,double element){

    if(self->allow_transaction){
        DtwTransaction_write_double(self->root_props->transaction,self->path,element);
    }
    else{
        dtw_write_double_file_content(self->path,element);
    }
    DtwResource_unload(self);
    self->loaded = true;
    char result[20] ={0};
    sprintf(result,"%lf",element);
    self->value_any = (unsigned char *)strdup(result);


}
void DtwResource_set_double_in_sub_resource(DtwResource *self,double element,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_double(created,element);
}

void DtwResource_set_bool( DtwResource *self,bool element){

    if(self->allow_transaction){
        DtwTransaction_write_bool(self->root_props->transaction,self->path,element);
    }
    else{
        dtw_write_bool_file_content(self->path,element);
    }

    DtwResource_unload(self);
    self->loaded = true;
    if(element){
        self->value_any = (unsigned char*)strdup("true");
    }
    else{
        self->value_any = (unsigned char*)strdup("false");

    }

}
void DtwResource_set_bool_in_sub_resource( DtwResource *self,bool element,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_bool(created,element);
}
