

#ifdef __linux__

bool private_dtw_verify_if_add(const int expected_type, int d_type);
bool private_dtw_verify_if_skip(struct dirent *entry);
#ifdef __cplusplus
struct DtwStringArray * dtw_list_basic(const char *path,int expected_type,bool concat_path=false);
#else 
struct DtwStringArray * dtw_list_basic(const char *path,int expected_type,bool concat_path);
#endif 


#endif