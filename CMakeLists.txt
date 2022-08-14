cmake_minimum_required(VERSION 3.0.0)
project(easy_log VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(easy_log_test)

target_include_directories(
    easy_log_test PRIVATE
    src/
)

target_sources(easy_log_test PRIVATE
    src/log_client.h
    src/log_client.cpp
    src/logger/logger.h
    src/logger/logger_test.cpp
    )

# include(CTest)
# enable_testing()
# add_subdirectory(third_party/google_test)
# include_directories(third_party/google_test/googletest/include)
