# Build and Install Guide

This document provides instructions for installing, compiling, and building the `DoTheWorld` library from scratch. It also covers how to mock dependencies for testing or dynamic compilation purposes.

## Installation

The `DoTheWorld` library can be easily integrated into your project by downloading the amalgamated source file and including it in your code. This approach simplifies the integration process by providing a single file that contains all necessary code.

### Steps to Install

1. **Download the Amalgamation File**:
   - You can download the amalgamated source file (`doTheWorldOne.c`) from the GitHub releases page.
   - Direct download link: [Amalgamation](https://github.com/OUIsolutions/DoTheWorld/releases/download/10.1.1/doTheWorldOne.c)
   - Alternatively, if you are on a Linux system, use the following command to download the file:
     ```bash
     curl -L https://github.com/OUIsolutions/DoTheWorld/releases/download/10.1.1/doTheWorldOne.c -o doTheWorldOne.c
     ```

2. **Include in Your Project**:
   - Copy the downloaded `doTheWorldOne.c` file into your project directory.
   - Include the file in your source code using the following directive:
     ```c
     #include "doTheWorldOne.c"
     ```

## Compilation

This section provides instructions for compiling the `DoTheWorld` library on different operating systems. Ensure that the library file (`doTheWorldOne.c`) is in your project directory or properly referenced in your build commands.

### Compile on Linux

To compile a project using the `DoTheWorld` library on Linux, use the `gcc` compiler with the following command. Replace `main.c` with the name of your source file if different.

```bash
gcc main.c -o your_output.out
```

**Notes**:
- Ensure that `doTheWorldOne.c` is in the same directory as `main.c`, or provide the correct path to the library file.
- The output binary will be named `your_output.out`. Adjust the name as needed using the `-o` flag.

### Compile on Windows

Compilation on Windows can be done using either Microsoft Visual C (MSVC) or MinGW64. Below are the commands for each.

#### Using Microsoft Visual C (MSVC)

Use the `cl.exe` compiler provided by MSVC to build your project. The following command assumes your source file is located in an `examples` directory and you want the output binary in a `bin` directory.

```cmd
cl.exe examples\example_simple.c /Fe:bin\example_simple.exe
```

**Notes**:
- Ensure that `doTheWorldOne.c` is accessible in the build context (e.g., in the same directory or included via a path).
- The `/Fe:` flag specifies the output executable name and path.

#### Using MinGW64

If you are using MinGW64, compile your project with the following command. This example also assumes your source file is in an `examples` directory.

```bash
i686-w64-mingw32-gcc examples\example_simple.c -o bin\example_simple.exe -lws2_32
```

**Notes**:
- The `-lws2_32` flag links against the Winsock library, which may be required for network-related functionality in `DoTheWorld`.
- Adjust paths and filenames as necessary for your project structure.

## Building from Scratch

If you prefer to build the `DoTheWorld` library from its source code rather than using the precompiled amalgamation, you will need to have the `Darwin` build tool installed on your system. This section guides you through the process.

### Prerequisites

- **Darwin Build Tool**: A utility required to build `DoTheWorld` from source.
  - Download and install `Darwin` using the following command on Linux:
    ```bash
    curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.020/darwin.out -o darwin.out && chmod +x darwin.out && sudo mv darwin.out /usr/bin/darwin
    ```
  - This command downloads the `Darwin` binary, makes it executable, and moves it to a system-wide executable path (`/usr/bin`).

### Build Steps

1. **Navigate to the Project Root Directory**:
   - Ensure you are in the root directory of the `DoTheWorld` project (where the `build/` folder exists).

2. **Run the Build Command**:
   - Use the `Darwin` tool to build the project with the following command:
     ```bash
     darwin run_blueprint build/ --mode folder
     ```
   - This command processes the build blueprint located in the `build/` directory and generates the release files.

3. **Locate Build Output**:
   - After a successful build, the generated release files will be placed in the `/release` directory within the project root.

**Notes**:
- Ensure `Darwin` is properly installed and accessible in your terminal before running the build command.
- If the build fails, check for error messages in the terminal output to troubleshoot issues such as missing dependencies or incorrect paths.

## Mocking Dependencies

For testing purposes or dynamic compilation, `DoTheWorld` supports mocking dependencies or their definitions. This is achieved by defining specific preprocessor macros before including the library in your code. These macros allow you to replace actual implementations with mock versions.

### Available Mocking Macros

Below are the preprocessor directives you can use to mock dependencies or their definitions. Define these macros before including `doTheWorldOne.c` in your source code.

- **Mocking cjSON Library**:
  - To mock the entire cjSON library (replace its implementation):
    ```c
    #define DTW_MOCK_CJSON
    ```
  - To mock only the cjSON definitions (e.g., for header-only mocking):
    ```c
    #define DTW_MOCK_CJSON_DEFINE
    ```

- **Mocking SHA256 Library**:
  - To mock the SHA256 implementation:
    ```c
    #define DTW_MOCK_SHA256
    ```
  - To mock only the SHA256 definitions:
    ```c
    #define DTW_MOCK_SHA256_DEFINE
    ```

### Usage Example

Here’s an example of how to use these macros in your code to mock dependencies before including the `DoTheWorld` library:

```c
// Mock the cjSON library implementation
#define DTW_MOCK_CJSON

// Mock the SHA256 definitions
#define DTW_MOCK_SHA256_DEFINE

// Include the DoTheWorld library after defining mocks
#include "doTheWorldOne.c"

int main() {
    // Your code here
    return 0;
}
```

**Notes**:
- Ensure that the mock definitions are placed before the `#include "doTheWorldOne.c"` directive to take effect.
- Mocking is particularly useful for unit testing or when you need to replace external dependencies with custom implementations.