cmake_minimum_required(VERSION 3.5...3.31)
project(Search_Engine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES
    src/main.cpp
    src/converter_json.cpp
    src/inverted_index.cpp
    src/search_server.cpp
)

set(TEST_SOURCES
    tests/test.cpp
    src/converter_json.cpp
    src/inverted_index.cpp
    src/search_server.cpp
)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
    nlohmann_json::nlohmann_json
    gtest_main
)

add_executable(run_tests ${TEST_SOURCES})

target_include_directories(run_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(run_tests 
    PRIVATE 
    nlohmann_json::nlohmann_json
    gtest_main
)


enable_testing()
include(GoogleTest)
gtest_discover_tests(run_tests)