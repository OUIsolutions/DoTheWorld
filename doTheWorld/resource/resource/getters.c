
unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary){
    DtwResource_load_if_not_loaded(self);
    *size = self->value_size;
    *is_binary = self->is_binary;
    return self->value_any;
}

unsigned char *DtwResource_get_any_from_sub_resource(DtwResource *self, long *size, bool *is_binary,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *element = DtwResource_sub_resource(self,"%s",name);
    return DtwResource_get_any(element,size,is_binary);

}

unsigned char *DtwResource_get_binary(DtwResource *self, long *size){
    bool is_binary;
    return DtwResource_get_any(self,size,&is_binary);
}

unsigned char *DtwResource_get_binary_from_sub_resource(DtwResource *self, long *size,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *element = DtwResource_sub_resource(self,"%s",name);
    return DtwResource_get_binary(element,size);
}


char *DtwResource_get_string(DtwResource *self){
    long size;
    bool is_binary;
    return (char *)DtwResource_get_any(self,&size,&is_binary);
}

char *DtwResource_get_string_from_sub_resource(DtwResource *self,const char *format,...){

    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *element = DtwResource_sub_resource(self,"%s",name);
    return DtwResource_get_string(element);
}


long DtwResource_get_long(DtwResource *self){
    char *element = DtwResource_get_string(self);
    if(!element){
        return DTW_NOT_FOUND;
    }
    long value;
    int result = sscanf(element,"%ld",&value);
    if(result == 0){
        return DTW_NOT_NUMERICAL;
    }
    return value;
}

long DtwResource_get_long_from_sub_resource(DtwResource *self,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *element = DtwResource_sub_resource(self,"%s",name);
    return DtwResource_get_long(element);
}


double DtwResource_get_double(DtwResource *self){
    char *element = DtwResource_get_string(self);
    if(!element){
        return DTW_NOT_FOUND;
    }
    double value;
    int result = sscanf(element,"%lf",&value);
    if(result == 0){
        return DTW_NOT_NUMERICAL;
    }
    return value;
}

double DtwResource_get_double_from_sub_resource(DtwResource *self,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *element = DtwResource_sub_resource(self,"%s",name);
    return DtwResource_get_double(element);
}


bool DtwResource_get_bool(DtwResource *self){
    char *element = DtwResource_get_string(self);
    if(strcmp(element,"true") == 0 || strcmp(element,"t") == 0){
        return true;
    }
    return false;
}
bool DtwResource_get_bool_from_sub_resource(DtwResource *self,const char *format,...){
    char name[2000] ={0};

    va_list args;
    va_start(args, format);
    vsprintf(name, format, args);
    va_end(args);

    DtwResource *element = DtwResource_sub_resource(self,"%s",name);
    return DtwResource_get_bool(element);
}