cmake_minimum_required(VERSION 3.8)
project(projekt)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c arguments.c requests.c requests.h)



add_executable(projekt ${SOURCE_FILES} requests.c requests.h)

find_package(OpenSSL)
target_link_libraries(projekt ${OPENSSL_LIBRARIES})