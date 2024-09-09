
#ifdef __linux__
#define dtw_create_dir(path) mkdir(path,0777)
#elif _WIN32
#define dtw_create_dir(path) _mkdir(path)

#endif


