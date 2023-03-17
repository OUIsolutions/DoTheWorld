
const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *dtw_base64_encode(const char *data, size_t input_length);

unsigned char *dtw_base64_decode(const char *data, size_t input_length, size_t *output_length);