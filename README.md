# 🌍 DoTheWorld

<div align="center">

![Version](https://img.shields.io/badge/version-10.1.1-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey.svg)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/OUIsolutions/DoTheWorld)

**A single-file C/C++ library for robust file system operations and data management**

[Installation](#installation) •
[Documentation](#documentation) •
[Features](#features) •
[Examples](#quick-examples) •
[Contributing](#contributing)

</div>

## 📋 Overview

DoTheWorld is a powerful Windows/Linux cross-platform library designed for comprehensive file and data handling in C/C++. From basic I/O operations to complex transactional systems, it provides a complete toolkit for file manipulation, encryption, hashing, and database-like functionality - all from a single file include.

## ✨ Features

<table>
  <tr>
    <td>
      <ul>
        <li>📁 File and directory management</li>
        <li>🔄 Atomic transactions</li>
        <li>🔒 Thread-safe lockers</li>
        <li>🔍 File search and listing</li>
        <li>⏱️ Modification date tracking</li>
      </ul>
    </td>
    <td>
      <ul>
        <li>🔐 SHA256 hashing</li>
        <li>📊 Base64 encoding/decoding</li>
        <li>🗄️ Resource management system</li>
        <li>🌲 Tree data structures</li>
        <li>🔀 Path manipulation utilities</li>
      </ul>
    </td>
    <td>
      <ul>
        <li>📦 Non-relational database</li>
        <li>🔑 Schema validation</li>
        <li>🚀 High-performance operations</li>
        <li>🔄 Copy and move operations</li>
        <li>🔐 Encryption capabilities</li>
      </ul>
    </td>
  </tr>
</table>

## 📦 Installation

### Option 1: {Single File Include}(https://github.com/OUIsolutions/DoTheWorld/releases/download/10.1.1/doTheWorld.c) (Recommended)

```c
// Just download and include
#include "doTheWorldOne.c"
```

### Option 2: Traditional [Header](https://github.com/OUIsolutions/DoTheWorld/releases/download/10.1.1/doTheWorld.h)/[Source](https://github.com/OUIsolutions/DoTheWorld/releases/download/10.1.1/doTheWorld.c)

```c
// Include the header in your code
#include "doTheWorld.h"

// And link with doTheWorld.c during compilation
```

## 📚 Documentation

| Category | Documentation Link | Description |
|----------|-------------------|-------------|
| 🏗️ **Setup** | [Build & Install](/docs/build_and_install.md) | Getting started with DoTheWorld |
| 📝 **Core I/O** | [Basic I/O](/docs/io.md) | Reading and writing files |
| 🔄 **Operations** | [Copy & Move](/docs/copy_and_move.md) | File and folder operations |
| 🔍 **Discovery** | [Listage](/docs/listage.md) | Listing files and directories |
| 🔢 **Encoding** | [Base64](/docs/base64.md) | Base64 encoding and decoding |
| 🔐 **Security** | [Hashers](/docs/hashers.md) | SHA256 and other hashing functions |
| ⏱️ **Tracking** | [Unix](/docs/unix.md) | Unix timestamp utilities |
| 🔒 **Concurrency** | [Locker](/docs/locker.md) | Thread-safe operations |
| 🗄️ **Resources** | [Resource System](/docs/resource.md) | Resource management framework |
| 🌲 **Structure** | [Tree](/docs/tree.md) | Tree data structure implementation |
| 🎲 **Random** | [Randomizers](/docs/randonizers.md) | Random generation utilities |
| ⚡ **Performance** | [Transactions](/docs/transactions.md) | Atomic transaction system |
| 🧩 **Components** | [Dependencies](/docs/dependencies.md) | Library dependencies |
| 🔐 **Security** | [Encryption](/docs/encryption.md) | Data encryption capabilities |

## 🚀 Quick Examples

### Reading and Writing Files

```c
#include "doTheWorldOne.c"

int main() {
    // Write a string to file
    dtw_write_string_to_file("hello.txt", "Hello, World!");
    
    // Read file content
    char *content = dtw_load_string_file("hello.txt");
    printf("%s\n", content);
    free(content);
    
    return 0;
}
```

### Using the Resource System

```c
#include "doTheWorldOne.c"

int main() {
    // Create a resource
    DtwResource *resource = new_DtwResource("my_data");
    
    // Set values
    DtwResource *user = DtwResource_sub_resource(resource, "user");
    DtwResource_set_string_in_sub_resource(user, "name", "John");
    DtwResource_set_long_in_sub_resource(user, "age", 30);
    
    // Commit changes
    DtwResource_commit(resource);
    DtwResource_free(resource);
    
    return 0;
}
```

## 📦 Releases

| Package | Description |
|---------|-------------|
| [doTheWorld.zip](https://github.com/OUIsolutions/DoTheWorld/releases/download/10.1.1/doTheWorld.zip) | Full package with all components |
| [doTheWorldOne.c](https://github.com/OUIsolutions/DoTheWorld/releases/download/10.1.1/doTheWorldOne.c) | Single-file amalgamated version |
| [doTheWorld.h](https://github.com/OUIsolutions/DoTheWorld/releases/download/10.1.1/doTheWorld.h) | Header declarations |
| [doTheWorld.c](https://github.com/OUIsolutions/DoTheWorld/releases/download/10.1.1/doTheWorld.c) | Source definitions |

## 🛠️ Build Toolchain

* [Darwin](https://github.com/OUIsolutions/Darwin) - Build management
* [Silver Chain](https://github.com/OUIsolutions/SilverChain) - Dependency management
* [CAmalgamator](https://github.com/OUIsolutions/CAmalgamator) - Code amalgamation

## 💡 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## ⭐ Support

If you find DoTheWorld useful, please consider giving it a star on GitHub!

---

<div align="center">
  <sub>Built with ❤️ by <a href="https://github.com/OUIsolutions">OUI Solutions</a></sub>
</div>
