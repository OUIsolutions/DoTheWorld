#include "doTheWorldOne.c"

const char *my_key = "my key";

void save_sub_resource(){
    DtwResource *resource = new_DtwResource("test");
    DtwEncriptionInterface *enc = newDtwAES_Custom_CBC_v1_interface(my_key);
    DtwResource_set_encryption(resource, enc, DTW_HEX_MODE);

    DtwResource_set_string_in_sub_resource(resource, "name", "mateus");

    DtwResource_commit(resource);
    DtwResource_free(resource);
    DtwEncriptionInterface_free(enc);    
}

void get_sub_resource(){
     DtwResource *resource = new_DtwResource("test");
    DtwEncriptionInterface *enc = newDtwAES_Custom_CBC_v1_interface(my_key);
    DtwResource_set_encryption(resource, enc, DTW_HEX_MODE);
    char *name = DtwResource_get_string_from_sub_resource(resource, "name");
    if(DtwResource_error(resource)){
        printf("error: %s\n", DtwResource_get_error_message(resource));
        DtwResource_commit(resource);
        DtwResource_free(resource);
        DtwEncriptionInterface_free(enc);    
        return; 
    }
    printf("name: %s\n", name);
    DtwResource_free(resource);
    DtwEncriptionInterface_free(enc);    
}

int main(){
    
    save_sub_resource();
    get_sub_resource();

}