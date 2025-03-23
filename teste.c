#include "src/one.c"
DtwNamespace dtw;

const char *my_key = "my key";

void save_sub_resource(){
    DtwResource *resource = dtw.resource.newResource("test");
    DtwEncriptionInterface *enc = dtw.encryption.newAES_Custom_CBC_v1_interface(my_key);
    dtw.resource.set_encryption(resource,enc,DTW_HEX_MODE);

    dtw.resource.set_string_in_sub_resource(resource,"name","mateus");

    dtw.resource.commit(resource);
    dtw.resource.free(resource);
    dtw.encryption.free(enc);    
}

void get_sub_resource(){
     DtwResource *resource = dtw.resource.newResource("test");
    DtwEncriptionInterface *enc = dtw.encryption.newAES_Custom_CBC_v1_interface(my_key);
    dtw.resource.set_encryption(resource,enc,DTW_HEX_MODE);
    char *name = dtw.resource.get_string_from_sub_resource(resource,"name");
    if(dtw.resource.error(resource)){
        printf("error: %s\n",dtw.resource.get_error_message(resource));
        dtw.resource.commit(resource);
        dtw.resource.free(resource);
        dtw.encryption.free(enc);    
        return; 
    }
    printf("name: %s\n",name);
        dtw.resource.free(resource);
    dtw.encryption.free(enc);    
}

int main(){
    dtw = newDtwNamespace();
    
    save_sub_resource();
    get_sub_resource();

}