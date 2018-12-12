cmake_minimum_required(VERSION 3.8)
project(projekt)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp arguments.cpp requests.cpp requests.h xml_reader.cpp xml_reader.h)

include_directories(/usr/include/libxml2/)

add_executable(projekt ${SOURCE_FILES} requests.cpp requests.h xml_reader.cpp xml_reader.h)

find_package(OpenSSL)
target_link_libraries(projekt ${OPENSSL_LIBRARIES} xml2)