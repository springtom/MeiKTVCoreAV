

cmake_minimum_required(VERSION 3.4.1)
set(lib_src_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
AUX_SOURCE_DIRECTORY(src/main/cpp/ DIR_SRCS)
add_library(sox STATIC IMPORTED)
set_target_properties(sox PROPERTIES IMPORTED_LOCATION
                             ${lib_src_DIR}/libsox.a)

add_library(
        coreav
        SHARED
        src/main/cpp/native-lib.cpp
        ${DIR_SRCS})


find_library(
              log-lib
              log )

target_link_libraries(
                       coreav
                       sox
                       ${log-lib} )