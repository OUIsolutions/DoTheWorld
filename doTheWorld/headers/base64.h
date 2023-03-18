
const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


unsigned char *dtw_base64_encode(unsigned char *data, size_t input_length);


unsigned char *dtw_base64_decode(unsigned char *data, size_t input_length, size_t *output_length);