#include  "doTheWorldOne.c"

int main(){
    const char *key ="what ever key you want to put with what ever size ";//can be any size
    DtwEncriptionInterface *enc = newDtwAES_Custom_CBC_v1_interface(key);
    unsigned char my_messsage[] = "what ever menssage you want to encrypt";
    long message_size = strlen(my_messsage);
    
    DtwEncriptionInterface_write_any_content(enc,"test.txt",my_messsage,message_size);

    long size;
    bool is_binary;
    unsigned char *decrypted_message = DtwEncriptionInterface_load_any_content(enc,"test.txt",&message_size,&is_binary);
    printf("decrypted message: %s\n",decrypted_message);
    free(decrypted_message);
    DtwEncriptionInterface_free(enc);

    return 0;

}