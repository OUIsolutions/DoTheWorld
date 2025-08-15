//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.fdeclare.h"
//silver_chain_scope_end


DtwEncryptionNamespace newDtwEncryptionNamespace(){
    DtwEncryptionNamespace self = {0};
    self.newAES_CBC_EncryptionInterface = newDtwAES_CBC_EncryptionInterface;
    self.newAES_CBC_EncryptionInterface_str = newDtwAES_CBC_EncryptionInterface_str;    
    self.newAES_ECB_EncryptionInterface = newDtwAES_ECB_EncryptionInterface;
    self.newAES_ECB_EncryptionInterface_str = newDtwAES_ECB_EncryptionInterface_str;
    self.newAES_Custom_CBC_v1_interface = newDtwAES_Custom_CBC_v1_interface;

    self.encrypt_buffer = DtwEncriptionInterface_encrypt_buffer;
    self.decrypt_buffer = DtwEncriptionInterface_decrypt_buffer;

    self.write_any_content = DtwEncriptionInterface_write_any_content;
    self.write_string_file_content = DtwEncriptionInterface_write_string_file_content;
    self.load_any_content = DtwEncriptionInterface_load_any_content;
    self.load_string_file_content = DtwEncriptionInterface_load_string_file_content;

    self.encrypt_buffer_hex = DtwEncriptionInterface_encrypt_buffer_hex;
    self.decrypt_buffer_hex = DtwEncriptionInterface_decrypt_buffer_hex;
    self.write_any_content_hex = DtwEncriptionInterface_write_any_content_hex;
    self.write_string_file_content_hex = DtwEncriptionInterface_write_string_file_content_hex;
    self.load_any_content_hex = DtwEncriptionInterface_load_any_content_hex;
    self.load_string_file_content_hex = DtwEncriptionInterface_load_string_file_content_hex;

    self.encrypt_buffer_b64 = DtwEncriptionInterface_encrypt_buffer_b64;
    self.decrypt_buffer_b64 = DtwEncriptionInterface_decrypt_buffer_b64;
    self.write_any_content_b64 = DtwEncriptionInterface_write_any_content_b64;
    self.write_string_file_content_b64 = DtwEncriptionInterface_write_string_file_content_b64;
    self.load_any_content_b64 = DtwEncriptionInterface_load_any_content_b64;
    self.load_string_file_content_b64 = DtwEncriptionInterface_load_string_file_content_b64;
    self.free = DtwEncriptionInterface_free;
    return self;
}