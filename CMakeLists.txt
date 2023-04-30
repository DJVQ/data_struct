cmake_minimum_required(VERSION 3.5)
project(data_struct VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(./src DIR_SRC)

set(PROJECT_SOURCES

        ${DIR_SRC}
        
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