# 🔍 Search Engine

Search engine for corporate portal. Final project of the "C++ Developer from Scratch" course.

[![C++](https://img.shields.io/badge/C++-20-blue?logo=c%2B%2B)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.25+-brightgreen?logo=cmake)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## 📋 Description

**Search Engine** is a console application written in C++ that indexes text files and performs search queries. The program is based on an inverted index, multithreaded indexing, and relevance-based ranking of search results.

## ✨ Features

- ✅ JSON configuration files
- ✅ Inverted index for fast search
- ✅ Multithreaded document indexing
- ✅ Relevance-based result ranking
- ✅ Unit testing with Google Test
- ✅ Cross-platform (Linux, Windows, macOS)

## 🛠 Tech Stack

- **C++20** — modern C++ standard
- **STL** — vectors, maps, algorithms
- **Multithreading** — std::thread, std::mutex
- **CMake** — build system
- **nlohmann/json** — JSON handling
- **Google Test** — unit testing

## 🚀 Quick Start

### Prerequisites
- C++20 compatible compiler (GCC 11+, Clang 14+, MSVC 2022)
- CMake 3.25 or higher
- Git

### Installation & Launch

```bash
# Clone repository
git clone https://github.com/4ek1tfy/Search_Engine.git
cd Search_Engine

# Build project
mkdir build && cd build
cmake ..
make

# Run program
./Search_Engine
```

### Run Tests

```bash
./run_tests
```

## 📄 Main Program (main.cpp)
The main.cpp file contains the main entry point of the search engine. It demonstrates the complete workflow of the application:

### What it does:
1. Creates Converter_JSON object    // Reads config.json and requests.json
2. Gets text documents              // Loads files specified in config
3. Updates document base            // Builds inverted index (multithreaded)
4. Gets search requests             // Reads queries from requests.json
5. Performs search                  // Processes all queries
6. Saves results                    // Writes answers.json
7. Prints status messages           // Shows progress

### Example output:
Search Engine started
Search Engine finished

### Code explanation:
```cpp
Converter_JSON cjs;                    // Handles all JSON operations
Inverted_Index idx;                    // Stores the inverted index
Search_Server srv(idx);                // Search server uses the index
std::vector<std::string> docs = cjs.get_text_documents();  // Load files
idx.update_document_base(docs);        // Build index (multithreaded)
std::vector<std::string> requests = cjs.get_requests();    // Get queries
std::vector<std::vector<relative_index>> result = srv.search(requests); // Search
cjs.put_answers(result);               // Save results to answers.json

## 📁 Project Structure

```
Search_Engine/
├── include/           # Header files
│   ├── converter_json.h
│   ├── inverted_index.h
│   └── search_server.h
├── src/               # Source files
│   ├── main.cpp
│   ├── converter_json.cpp
│   ├── inverted_index.cpp
│   └── search_server.cpp
├── tests/             # Tests
│   └── test.cpp
├── data/              # Example data
│   ├── file001.txt
│   ├── file002.txt
│   ├── config.json
│   └── requests.json
├── CMakeLists.txt     # Build configuration
└── README.md          # This file
```

## ⚙️ Configuration

### config.json
```json
{
  "config": {
    "name": "Search_Engine",
    "version": "1.0.0",
    "max_responses": 5
  },
  "files": [
    "file001.txt",
    "file002.txt"
  ]
}
```

### requests.json
```json
{
  "requests": [
    "milk water",
    "sugar"
  ]
}
```

## 📊 Search Results

### Example answers.json
```json
{
  "answers": {
    "request001": {
      "result": "true",
      "relevance": [
        {"docid": 2, "rank": 1.0},
        {"docid": 0, "rank": 0.7},
        {"docid": 1, "rank": 0.3}
      ]
    },
    "request002": {
      "result": "false"
    }
  }
}
```

## 🧪 Testing

The project is covered with unit tests that verify:
- Correct inverted index construction
- Handling of missing words
- Proper relevance ranking
- Result limit (top-5)

All tests pass successfully:
```
[==========] 5 tests from 2 test suites ran.
[  PASSED  ] 5 tests.
```

## 📝 License

This project is licensed under the MIT License. See the LICENSE file for details.

---

<div align="center">
  <sub>© 2026 Search Engine. Author: Krasovski Stanislav</sub>
</div>