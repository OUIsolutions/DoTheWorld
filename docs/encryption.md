# DoTheWorld Encryption System Documentation

This document provides detailed information on the encryption system within the DoTheWorld (DTW) library. It covers the primary encryption interface, supported encryption modes, methods for encryption and decryption, file operations, integration with other DTW components, and best practices for error handling.

## Overview of DtwEncryptionInterface

The `DtwEncryptionInterface` is the core component of the DTW encryption system, encapsulating both encryption and decryption functionalities. Instances of this interface are created using specific initialization methods provided by the library's namespace, tailored to different encryption modes and key formats.

## Supported Encryption Modes

The library supports two primary AES (Advanced Encryption Standard) encryption modes: CBC (Cipher Block Chaining) and ECB (Electronic Codebook). Each mode has unique characteristics and initialization methods.

### AES-CBC (Cipher Block Chaining)

CBC mode uses both a key and an initialization vector (IV) to ensure secure encryption. The IV introduces randomness, making each encryption unique even with the same key and data.

#### Initialization Methods for AES-CBC

1. **Using Raw Key and IV Bytes**:
   This method allows direct specification of key and IV as byte arrays. The maximum size for both key and IV is 16 bytes.
   ```c
   uint8_t key[] = {56, 31, 4, 56, 7, 1, 31, 6, 7, 8}; // Max 16 bytes
   uint8_t iv[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; // 16 bytes
   int key_size = sizeof(key) - 1;
   int iv_size = sizeof(iv) - 1;
   
   DtwEncryptionInterface *enc = newDtwAES_CBC_EncryptionInterface(key, key_size, iv, iv_size);
   ```
   [Full Example](/examples/encryption/cbc_encryption_initializer_key.c)

2. **Using String Key and IV**:
   This method accepts key and IV as null-terminated strings, with a maximum length of 16 characters each.
   ```c
   const char *key = "my custom key"; // Max 16 chars
   const char *iv = "my custom iv";   // Max 16 chars
   
   DtwEncryptionInterface *enc = newDtwAES_CBC_EncryptionInterface_str(key, iv);
   ```
   [Full Example](/examples/encryption/cbc_encryption_initializer_str.c)

3. **Using Custom CBC Implementation (v1)**:
   A custom implementation of CBC that allows keys of any size, removing the 16-byte restriction.
   ```c
   const char *key = "what ever key you want to put with what ever size"; // No size limit
   
   DtwEncryptionInterface *enc = newDtwAES_Custom_CBC_v1_interface(key);
   ```
   [Full Example](/examples/encryption/cbc_encryption_custom_v1_inicializer.c)

### AES-ECB (Electronic Codebook)

ECB mode encrypts each block of data independently using only a key (no IV is required). Note that ECB is generally less secure than CBC for most applications due to its lack of randomization.

#### Initialization Methods for AES-ECB

1. **Using Raw Key Bytes**:
   Specify the key as a byte array with a maximum size of 16 bytes.
   ```c
   uint8_t key[] = {56, 31, 4, 56, 7, 1, 31, 6, 7, 8}; // Max 16 bytes
   int key_size = sizeof(key) - 1;
   
   DtwEncryptionInterface *enc = newDtwAES_ECB_EncryptionInterface(key, key_size);
   ```
   [Full Example](/examples/encryption/ecb_encryption_initializer_key.c)

2. **Using String Key**:
   Specify the key as a null-terminated string with a maximum length of 16 characters.
   ```c
   const char *key = "my custom key"; // Max 16 chars
   
   DtwEncryptionInterface *enc = newDtwAES_ECB_EncryptionInterface_str(key);
   ```
   [Full Example](/examples/encryption/ecb_encryption_initializer_str.c)

## Encryption and Decryption Methods

The `DtwEncryptionInterface` provides methods to encrypt and decrypt data in various formats, catering to different use cases.

### Supported Output Formats

Encrypted data can be output in one of three formats:
- **Raw Buffer**: Binary data, suitable for direct storage or transmission.
- **Hexadecimal String**: Text representation using hexadecimal characters, useful for readable output.
- **Base64 String**: Text representation using Base64 encoding, ideal for embedding in text-based formats like JSON.

### Buffer Encryption

#### Raw Buffer Output
Encrypts data into a binary format.
```c
long encrypted_size = 0;
unsigned char *encrypted = DtwEncryptionInterface_encrypt_buffer(enc, data, data_size, &encrypted_size);
```
[Full Example](/examples/encryption/raw_buffer_example.c)

#### Hexadecimal Format Output
Encrypts data and returns it as a hexadecimal string.
```c
const char *hex_encrypted = DtwEncryptionInterface_encrypt_buffer_hex(enc, data, data_size);
```
[Full Example](/examples/encryption/hex_buffer_example.c)

#### Base64 Format Output
Encrypts data and returns it as a Base64-encoded string.
```c
const char *b64_encrypted = DtwEncryptionInterface_encrypt_buffer_b64(enc, data, data_size);
```
[Full Example](/examples/encryption/b64_buffer.c)

### Buffer Decryption

#### Raw Buffer Input
Decrypts binary data and returns the decrypted content.
```c
long decrypted_size = 0;
bool is_binary = false;
unsigned char *decrypted = DtwEncryptionInterface_decrypt_buffer(enc, encrypted, encrypted_size, &decrypted_size, &is_binary);
```
[Full Example](/examples/encryption/raw_buffer_example.c)

#### Hexadecimal Format Input
Decrypts a hexadecimal string and returns the decrypted content.
```c
long decrypted_size = 0;
bool is_binary = false;
unsigned char *decrypted = DtwEncryptionInterface_decrypt_buffer_hex(enc, hex_encrypted, &decrypted_size, &is_binary);
```
[Full Example](/examples/encryption/hex_buffer_example.c)

#### Base64 Format Input
Decrypts a Base64-encoded string and returns the decrypted content.
```c
long decrypted_size = 0;
bool is_binary = false;
unsigned char *decrypted = DtwEncryptionInterface_decrypt_buffer_b64(enc, b64_encrypted, &decrypted_size, &is_binary);
```
[Full Example](/examples/encryption/b64_buffer.c)

## File Operations

The library supports reading and writing encrypted content directly to files, simplifying secure storage.

### Writing Encrypted Content to Files
Encrypts the provided data and writes it to a specified file.
```c
DtwEncryptionInterface_write_any_content(enc, "filename.txt", data, data_size);
```
[Full Example](/examples/encryption/saving_and_reading_to_file.c)

### Reading Encrypted Content from Files
Reads and decrypts content from a specified file.
```c
long size;
bool is_binary;
unsigned char *decrypted = DtwEncryptionInterface_load_any_content(enc, "filename.txt", &size, &is_binary);
```
[Full Example](/examples/encryption/saving_and_reading_to_file.c)

## Integration with Other DTW Components

The encryption system integrates seamlessly with other components of the DTW library, such as transactions and resources.

### DtwTransaction
Transactions can be encrypted to secure data during operations.
```c
DtwTransaction *t = newDtwTransaction();
DtwEncryptionInterface *enc = newDtwAES_Custom_CBC_v1_interface("my encryption key");
DtwTransaction_set_encryption(t, enc, DTW_HEX_MODE);

// Use transaction as normal
DtwTransaction_write_string(t, "file.txt", "content");
DtwTransaction_commit(t, "directory/");
```
[Full Example](/examples/encryption/encrypted_transaction.c)

### DtwResource
Resources can be encrypted to protect their contents.
```c
DtwResource *resource = new_DtwResource("resource_name");
DtwEncryptionInterface *enc = newDtwAES_Custom_CBC_v1_interface("my key");
DtwResource_set_encryption(resource, enc, DTW_HEX_MODE);

// Use resource as normal
DtwResource_set_string_in_sub_resource(resource, "key", "value");
DtwResource_commit(resource);
```
[Full Example](/examples/encryption/resource.c)

## Available Output Modes

When setting encryption for resources or transactions, specify the output format using one of the following constants:
- `DTW_RAW_MODE`: Raw binary output.
- `DTW_HEX_MODE`: Hexadecimal string output.
- `DTW_B64_MODE`: Base64 string output.

## Error Handling

Encryption and decryption operations may fail due to invalid keys, corrupted data, or other issues. Always check for `NULL` returns to handle errors gracefully.
```c
if (encrypted == NULL) {
    printf("Error encrypting\n");
    return 1;
}
```

## Key Size Limitations

- For standard AES-CBC and AES-ECB interfaces, both key and IV (if applicable) must be under 16 bytes.
- For the custom CBC v1 interface, the key can be of any size, offering greater flexibility.

## Notes

- Ensure that keys and IVs are securely generated and stored to prevent unauthorized access to encrypted data.
- ECB mode is not recommended for sensitive data due to its deterministic nature, which can reveal patterns in the encrypted output.
- Always refer to the full examples linked in this documentation for complete and context-specific usage.
