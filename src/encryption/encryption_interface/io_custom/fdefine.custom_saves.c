

bool private_DtwEncriptionInterface_write_any_content_custom_mode(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size,short mode){
    if(mode == DTW_RAW_MODE){
        return DtwEncriptionInterface_write_any_content(self,file_name,value,size);
    }
    if(mode == DTW_B64_MODE){
        return DtwEncriptionInterface_write_any_content_b64(self,file_name,value,size);
    }
    if(mode == DTW_HEX_MODE){
        return DtwEncriptionInterface_write_any_content_hex(self,file_name,value,size);
    }
    return false;
}


unsigned char *private_DtwEncriptionInterface_load_any_content_custom_mode(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary,short mode){
    if(mode == DTW_RAW_MODE){
        return DtwEncriptionInterface_load_any_content(self,file_name,out_size,is_binary);
    }
    if(mode == DTW_B64_MODE){
        return DtwEncriptionInterface_load_any_content_b64(self,file_name,out_size,is_binary);
    }
    if(mode == DTW_HEX_MODE){
        return DtwEncriptionInterface_load_any_content_hex(self,file_name,out_size,is_binary);
    }
    *is_binary = false;
    *out_size = 0;
    return NULL;
}