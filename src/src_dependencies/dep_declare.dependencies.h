


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include <stdarg.h>

#include <errno.h>



#ifdef __linux__
#include <unistd.h>
#include <sys/time.h>
#include <sys/file.h>

#include <sys/wait.h>
  #include <dirent.h>
  #include <unistd.h>
#elif _WIN32
  #include <windows.h>
  #include <tchar.h>
  #include <wchar.h>
  #include <locale.h>
  #include <direct.h>
#endif

#if !defined(cJSON__h)
#include "../../dependencies/cJSON.h"
#define DTW_CJSON_IMPLEMENTED
#endif

#if !defined(SHA_256_H)
#include "../../dependencies/sha-256.h"
#define DTW_SHA256_IMPLEMENTED
#endif