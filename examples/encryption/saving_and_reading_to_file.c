
#include  "doTheWorldOne.c"


DtwNamespace dtw;

int main(){
    dtw = newDtwNamespace();
    const char *key ="what ever key you want to put with what ever size ";//can be any size
    DtwEncriptionInterface *enc = dtw.encryption.newAES_Custom_CBC_v1_interface(key);
    unsigned char my_messsage[] = "what ever menssage you want to encrypt";
    long message_size = strlen(my_messsage);
    
    dtw.encryption.write_any_content(enc,"test.txt",my_messsage,message_size);

    long size;
    bool is_binary;
    unsigned char *decrypted_message = dtw.encryption.load_any_content(enc,"test.txt",&message_size,&is_binary);
    printf("decrypted message: %s\n",decrypted_message);
    free(decrypted_message);
    dtw.encryption.free(enc);

    return 0;

}