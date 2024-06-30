# Project setup
cmake_minimum_required(VERSION 3.5)
project(BCrypt)
set(CMAKE_CXX_STANDARD 14)

# Profiles
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
endif()

# Output path
set(OutputDirectory "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OutputDirectory}/obj")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OutputDirectory}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OutputDirectory}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

# Install   
install (TARGETS BCrypt 
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ 
    DESTINATION include)

install (FILES halfooda-bcrypt.conf
    DESTINATION etc)

