# DoTheWorld Encryption System Documentation

### DtwEncriptionInterface

The primary encryption interface that encapsulates encryption/decryption functionality. Created through the namespace's encryption methods.

## Encryption Modes

### AES-CBC (Cipher Block Chaining)

CBC mode requires both a key and an initialization vector (IV).

#### Initialization Methods:
[Full Example](/examples/encryption/cbc_encryption_initializer_key.c)
1. **Using raw key and IV bytes**:
   ```c
   uint8_t key[] = {56, 31, 4, 56, 7, 1, 31, 6, 7, 8}; // Max 16 bytes
   uint8_t iv[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
   int key_size = sizeof(key) - 1;
   int iv_size = sizeof(iv) - 1;
   
   DtwEncriptionInterface *enc = newDtwAES_CBC_EncryptionInterface(key, key_size, iv, iv_size);
   ```

2. **Using string key and IV**:
[Full Example](/examples/encryption/cbc_encryption_initializer_str.c)
   ```c
   const char *key = "my custom key"; // Max 16 chars
   const char *iv = "my custom iv";   // Max 16 chars
   
   DtwEncriptionInterface *enc = newDtwAES_CBC_EncryptionInterface_str(key, iv);
   ```

3. **Using custom CBC implementation (v1)**:
[Full Example](/examples/encryption/cbc_encryption_custom_v1_inicializer.c)
   ```c
   const char *key = "what ever key you want to put with what ever size"; // No size limit
   
   DtwEncriptionInterface *enc = newDtwAES_Custom_CBC_v1_interface(key);
   ```

### AES-ECB (Electronic Codebook)

ECB mode requires only a key (no IV).

#### Initialization Methods:
[Full Example](/examples/encryption/ecb_encryption_initializer_key.c)
1. **Using raw key bytes**:
   ```c
   uint8_t key[] = {56, 31, 4, 56, 7, 1, 31, 6, 7, 8}; // Max 16 bytes
   int key_size = sizeof(key) - 1;
   
   DtwEncriptionInterface *enc = newDtwAES_ECB_EncryptionInterface(key, key_size);
   ```

2. **Using string key**:
[Full Example](/examples/encryption/ecb_encryption_initializer_str.c)
   ```c
   const char *key = "my custom key"; // Max 16 chars
   
   DtwEncriptionInterface *enc = newDtwAES_ECB_EncryptionInterface_str(key);
   ```

## Encryption/Decryption Methods

### Output Formats

The library supports three output formats for encrypted data:

1. **Raw buffer**: Binary output
2. **Hexadecimal string**: Text representation using hexadecimal characters
3. **Base64 string**: Text representation using base64 encoding

### Buffer Encryption

#### Raw Buffer
[Full Example](/examples/encryption/raw_buffer_example.c)
```c
long encrypted_size = 0;
unsigned char *encrypted = DtwEncriptionInterface_encrypt_buffer(enc, data, data_size, &encrypted_size);
```

#### Hexadecimal Format
[Full Example](/examples/encryption/hex_buffer_example.c)
```c
const char *hex_encrypted = DtwEncriptionInterface_encrypt_buffer_hex(enc, data, data_size);
```

#### Base64 Format
[Full Example](/examples/encryption/b64_buffer.c)
```c
const char *b64_encrypted = DtwEncriptionInterface_encrypt_buffer_b64(enc, data, data_size);
```

### Buffer Decryption

#### Raw Buffer
[Full Example](/examples/encryption/b64_buffer.c)

```c
long decrypted_size = 0;
bool is_binary = false;
unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer(enc, encrypted, encrypted_size, &decrypted_size, &is_binary);
```

#### Hexadecimal Format
[Full Example](/examples/encryption/hex_buffer_example.c)
```c
long decrypted_size = 0;
bool is_binary = false;
unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer_hex(enc, hex_encrypted, &decrypted_size, &is_binary);
```

#### Base64 Format
[Full Example](/examples/encryption/b64_buffer.c)
```c
long decrypted_size = 0;
bool is_binary = false;
unsigned char *decrypted = DtwEncriptionInterface_decrypt_buffer_b64(enc, b64_encrypted, &decrypted_size, &is_binary);
```

## File Operations

### Writing Encrypted Content to Files
[Full Example](/examples/encryption/saving_and_reading_to_file.c)
```c
DtwEncriptionInterface_write_any_content(enc, "filename.txt", data, data_size);
```

### Reading Encrypted Content from Files
[Full Example](/examples/encryption/saving_and_reading_to_file.c)
```c
long size;
bool is_binary;
unsigned char *decrypted = DtwEncriptionInterface_load_any_content(enc, "filename.txt", &size, &is_binary);
```

## Integration with Other DTW Components

### DtwTransaction
[Full Example](/examples/encryption/encrypted_transaction.c)
Transactions can be encrypted:

```c
DtwTransaction *t = newDtwTransaction();
DtwEncriptionInterface *enc = newDtwAES_Custom_CBC_v1_interface("my encryption key");
DtwTransaction_set_encryption(t, enc, DTW_HEX_MODE);

// Use transaction as normal
DtwTransaction_write_string(t, "file.txt", "content");
DtwTransaction_commit(t, "directory/");
```

### DtwResource

Resources can also be encrypted:
[Full Example](/examples/encryption/resource.c)
```c
DtwResource *resource = new_DtwResource("resource_name");
DtwEncriptionInterface *enc = newDtwAES_Custom_CBC_v1_interface("my key");
DtwResource_set_encryption(resource, enc, DTW_HEX_MODE);

// Use resource as normal
DtwResource_set_string_in_sub_resource(resource, "key", "value");
DtwResource_commit(resource);
```


## Encryption Modes

### Available Output Modes

When setting encryption for resources or transactions:

```c
// Constants for setting the output format
DTW_RAW_MODE  // For raw buffer output
DTW_HEX_MODE  // For hexadecimal output
DTW_B64_MODE  // For base64 output
```

## Error Handling

Always check for NULL returns on encryption/decryption operations:

```c
if (encrypted == NULL) {
    printf("Error encrypting\n");
    return 1;
}
```


## Key Size Limitations

- For standard AES-CBC and AES-ECB interfaces, the key and IV size must be under 16 bytes.
- For the custom CBC v1 interface, the key can be any size.
