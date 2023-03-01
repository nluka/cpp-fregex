# cpp-fregex

Tiny library for file matching using regular expressions in C++.

## Using

This is a source-based library, so copy [fregex.cpp](/fregex.cpp) and [fregex.hpp](/fregex.hpp) into your project and `#include "fregex.hpp"` where you need it. That's it.

## Example

```
root
│  file1.txt
│  file2.txt
|
└───dir1
│   │  file3.txt
│   │
│   └───dir2
│       │  file4.txt
│       │  _file.txt
│
└───dir3
    │  file5.txt
    │  _file.txt
```

```cpp
std::vector<std::filesystem::path> matches = fregex::find(
  "root",             // 1. search path
  "file[2-5]\\.txt",  // 2. regular expression
  true,               // 3. recursive search, off by default
  "debug.log",        // 4. path to debug log file, none by default
);

// matches:
//    root/file2.text
//    root/dir1/file3.txt
//    root/dir1/dir2/file4.txt
//    root/dir3/file5.txt
```
