cmake_minimum_required(VERSION 3.5)
project(data_struct VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES

        src/head/head.h

        src/head/sort.h
        
        main.cpp
)

if(ANDROID)

    add_library(data_struct SHARED

        ${PROJECT_SOURCES}

    )

else()

    add_executable(data_struct

        ${PROJECT_SOURCES}

    )

endif()