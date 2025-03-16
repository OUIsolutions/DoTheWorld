

## Install

To install the lib just copy the [Amalgamation](https://github.com/OUIsolutions/DoTheWorld/releases/download/9.0.002/doTheWorldOne.c) into your project and include it in your code:
```c
#include "BearHttpsClientOne.c"
```


If  you are on Linux, you can download the lib with:
```bash
curl -L https://github.com/OUIsolutions/DoTheWorld/releases/download/9.0.002/doTheWorldOne.c -o doTheWorldOne.c
```

## Compile on Linux

To compile the lib in **Linux** you can use the following command:
```bash
gcc main.c -o your_output.out
```

## Compile on Windows

To compile the lib in **Windows** you can use the following commands

With Microsoft Visual C:
```cmd
cl.exe examples\example_simple.c /Fe:bin\example_simple.exe
```

With mingw64:
```bash
i686-w64-mingw32-gcc examples\example_simple.c -o bin\example_simple.exe -lws2_32
```

## Build from scratch

For buiding from scratch you need to have [darwin](https://github.com/OUIsolutions/Darwin/) installed on your machine. To install darwin:
```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.020/darwin.out -o darwin.out && chmod +x darwin.out &&  sudo  mv darwin.out /usr/bin/darwin
```

Then you can build the project with in the root dir of the project:
```bash
darwin run_blueprint build/  --mode folder
```

It will generate all the **releases** in the **/release** dir.



### Mocking dependencies or dependencies implementations

The following defines toggle dependencies or just the definitions.
It is useful for  working with dynamic compilation or mocking dependencies.
```c
// Mocks cjSON library
#define DTW_MOCK_CJSON

// Mocks cjSON definitions
#define DTW_MOCK_CJSON_DEFINE

// Mocks sha256 
#define DTW_MOCK_SHA256

// Mocks sha256 definitions
#define DTW_MOCK_SHA256_DEFINE
// all these flags must be seted before including the lib
#include "doTheWorldOne.c"
```
