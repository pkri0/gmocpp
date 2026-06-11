cmake_minimum_required(VERSION 3.23)

project(gmocpp)
set(GAMS_DISTRIB_MAJOR 52)
set(GAMS_DISTRIB C:/GAMS/${GAMS_DISTRIB_MAJOR})
set(GAMS_DISTRIB_C_API "${GAMS_DISTRIB}/apifiles/C/api")
include_directories(${GAMS_DISTRIB_C_API})

add_library(gmocppdll MODULE)

target_sources(gmocppdll
    PRIVATE
        gmocpp.cpp
        gevmcc.c
        gmomcc.c
)
