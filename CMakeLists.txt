cmake_minimum_required(VERSION 3.10)
project(CPulse LANGUAGES CXX)

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)

# Add LLVM definitions and include directories to the project
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable exceptions
if(MSVC)
    # MSVC-specific flag to disable exceptions
    add_compile_options(/EHsc-)
else()
    # GCC/Clang flag to disable exceptions
    add_compile_options(-fno-exceptions)
endif()

# Add source files
add_executable(CPulse
    CPulse.cpp
    CPulse.h
    Classes/Lexer.cpp
    Classes/Lexer.h
    Classes/Enums/TokenTypes.h
    Classes/Structs/Token.h
    Classes/Parser.h
    Classes/Parser.cpp
    Classes/AST.h
    Classes/AST.CPP
    Classes/CodeGenerator.h
    # Assuming CodeGenerator.cpp should also be included
    Classes/CodeGenerator.cpp
)

# Include directories
include_directories("Classes" "Classes/Enums" "Classes/Structs")

# Link against LLVM libraries (specify required libraries)
llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(CPulse ${llvm_libs})

# Optionally, to use the latest draft features with MSVC
if(MSVC)
    target_compile_options(CPulse PRIVATE "/std:c++latest")
endif()