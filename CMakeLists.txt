# Project setup
cmake_minimum_required(VERSION 3.5)
project(bcrypt VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Profiles
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
endif()

# Creates the compile_commands.json file for your LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create symlink for compile_commands.json in root dir for lsp
execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)

# Output path
set(OutputDirectory "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OutputDirectory}/obj")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OutputDirectory}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OutputDirectory}")

# Add the subdirectories
add_subdirectory(src)
add_subdirectory(test)

# Build the test project
add_executable(bcrypt_test 
    ${TEST_SRC_FILES}
)

# Add the include files to avoid relative paths
target_include_directories(bcrypt_test PRIVATE src)
target_include_directories(bcrypt_test PRIVATE include)
target_include_directories(bcrypt PRIVATE include)

# Link the needed libs
target_link_libraries(bcrypt_test bcrypt)

# Install   
install (TARGETS bcrypt LIBRARY DESTINATION lib)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
