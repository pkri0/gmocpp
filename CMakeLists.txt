cmake_minimum_required(VERSION 3.30)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(CMAKE_CXX_MODULE_STD 1)
project(gmocpp LANGUAGES CXX C)
set(GAMS_DISTRIB_MAJOR 52)
set(GAMS_DISTRIB C:/GAMS/${GAMS_DISTRIB_MAJOR})
set(GAMS_DISTRIB_C_API "${GAMS_DISTRIB}/apifiles/C/api")
include_directories(${GAMS_DISTRIB_C_API})
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
add_library(gmocpplib MODULE)

target_compile_features(gmocpplib
  PRIVATE   cxx_std_23
 )

target_sources(gmocpplib
    PRIVATE
        gmocpp.cpp
        gevmcc.c
        gmomcc.c
)
