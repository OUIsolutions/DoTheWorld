#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef __linux__
  #include <dirent.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <unistd.h>
#elif _WIN32
  #include <windows.h>
  #include <tchar.h>
  #include <wchar.h>
  #include <locale.h>
#endif
