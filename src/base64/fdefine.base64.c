
char *dtw_base64_encode(unsigned char *data, long input_length) {
    // Base64 character table
    static const char base64_chars[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    // Parameter validation
    if (data == NULL || input_length < 0) {
        return NULL;
    }
    
    // Calculate required output size
    size_t output_length = 4 * ((input_length + 2) / 3);
    
    // Allocate memory for output string (including space for null terminator)
    char *encoded_data = (char *)malloc(output_length + 1);
    if (encoded_data == NULL) {
        return NULL; // Memory allocation failure
    }
    
    // Encoding process
    size_t i = 0;
    size_t j = 0;
    unsigned int triple;
    
    // Process full triplets of bytes (3 bytes at a time)
    for (i = 0, j = 0; i + 2 < input_length; i += 3) {
        triple = (data[i] << 16) | (data[i + 1] << 8) | data[i + 2];
        
        encoded_data[j++] = base64_chars[(triple >> 18) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 12) & 0x3F];
        encoded_data[j++] = base64_chars[(triple >> 6) & 0x3F];
        encoded_data[j++] = base64_chars[triple & 0x3F];
    }
    
    // Handle remaining bytes with padding
    if (i < input_length) {
        // One or two bytes remain
        if (i + 1 < input_length) {
            // Two bytes remain
            triple = (data[i] << 16) | (data[i + 1] << 8);
            
            encoded_data[j++] = base64_chars[(triple >> 18) & 0x3F];
            encoded_data[j++] = base64_chars[(triple >> 12) & 0x3F];
            encoded_data[j++] = base64_chars[(triple >> 6) & 0x3F];
            encoded_data[j++] = '=';
        } else {
            // One byte remains
            triple = data[i] << 16;
            
            encoded_data[j++] = base64_chars[(triple >> 18) & 0x3F];
            encoded_data[j++] = base64_chars[(triple >> 12) & 0x3F];
            encoded_data[j++] = '=';
            encoded_data[j++] = '=';
        }
    }
    
    // Add null terminator
    encoded_data[j] = '\0';
    
    return encoded_data;
}


unsigned char *dtw_base64_decode(const char *data, long *output_length) {
    // Base64 decoding table (value for each character)
    static const unsigned char decoding_table[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0,
        0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    
    // Parameter validation
    if (data == NULL || output_length == NULL) {
        return NULL;
    }
    
    long input_length = strlen(data);
    
    // Check if length is a multiple of 4
    if (input_length % 4 != 0) {
        return NULL;
    }
    
    // Calculate output size
    *output_length = input_length / 4 * 3;
    
    // Adjust size if padding is present
    if (input_length > 0) {
        if (data[input_length - 1] == '=') (*output_length)--;
        if (input_length >= 2 && data[input_length - 2] == '=') (*output_length)--;
    }
    
    // Allocate memory for decoded data
    unsigned char *decoded_data = (unsigned char*)malloc(*output_length + 1);
    if (decoded_data == NULL) {
        return NULL; // Memory allocation failure
    }
    
    // Decoding process
    size_t i = 0;
    size_t j = 0;
    
    while (i < input_length) {
        // Get 4 characters from Base64 string
        unsigned char a = data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]]; i++;
        unsigned char b = data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]]; i++;
        unsigned char c = data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]]; i++;
        unsigned char d = data[i] == '=' ? 0 : decoding_table[(unsigned char)data[i]]; i++;
        
        // Combine 4 groups of 6 bits into 3 bytes
        unsigned int triple = (a << 18) | (b << 12) | (c << 6) | d;
        
        if (j < *output_length) decoded_data[j++] = (triple >> 16) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = triple & 0xFF;
    }
    
    // Add null terminator
    decoded_data[*output_length] = '\0';
    
    return decoded_data;
}



char *dtw_convert_binary_file_to_base64(const char *path){
     long size;
     unsigned char *data  = dtw_load_binary_content(path, &size);
    char *b64   = dtw_base64_encode(data, size);
    free(data);
    return b64;
}
