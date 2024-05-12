
void DtwResource_set_binary_sha_in_sub_resource(DtwResource *self, unsigned  char *value, long size, const char *format, ...){
    if(DtwResource_error(self)){
        return;
    }
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_binary_sha(created,value,size);
}

void DtwResource_set_string_sha_in_sub_resource(DtwResource *self,const char *value,const char *format,...){
    if(DtwResource_error(self)){
        return;
    }
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_string_sha(created,value);
}

void DtwResource_set_string_in_sub_resource(DtwResource *self,const  char *element,const char *format,...){
    if(DtwResource_error(self)){
        return ;
    }
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_string(created,element);
}

void DtwResource_set_long_in_sub_resource(DtwResource *self,long element,const char *format,...){
    if(DtwResource_error(self)){
        return ;
    }
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_long(created,element);
}
void DtwResource_set_double_in_sub_resource(DtwResource *self,double element,const char *format,...){
    if(DtwResource_error(self)){
        return ;
    }
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_double(created,element);
}

void DtwResource_set_bool_in_sub_resource( DtwResource *self,bool element,const char *format,...){
    if(DtwResource_error(self)){
        return ;
    }
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *created = DtwResource_sub_resource(self,"%s",name);
    DtwResource_set_bool(created,element);
}
