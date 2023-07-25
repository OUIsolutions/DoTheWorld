


long dtw_load_long_file_content(const char * path){
    char *data = dtw_load_string_file_content(data);
    if(!data){
        return -1;
    }
    long result = -1;
    sscanf(data,"ld", &result);
    return result;
}

double dtw_load_double_file_content(const char * path){
    char *data = dtw_load_string_file_content(data);
    if(!data){
        return -1;
    }
    double result = -1;
    sscanf(data,"%lf",&result);
    return result;
}

bool dtw_load_bool_file_content(const char * path){
    char *data = dtw_load_string_file_content(data);
    if(!data){
        return false;
    }
    if(strcmp(data,"true") == 0 || strcmp(data,"t") == 0){
        return true;
    }
    return false;
}


int dtw_complex_entity_type(const char *path){
    return dtw_entity_type(path);
}

void dtw_write_long_file_content(const char *path, long value){
    char result[30] ={0};
    sprintf(result,"%ld",value);
    dtw_write_string_file_content(path,result);
}


void dtw_write_double_file_content(const char *path,double value){
    char result[30] ={0};
    sprintf(result,"%lf",value);
    dtw_write_string_file_content(path,result);
}


void dtw_write_bool_file_content(const char *path, bool value){
    if(value){
        dtw_write_string_file_content(path,"t");
    }
    else{
        dtw_write_string_file_content(path,"f");
    }
}


