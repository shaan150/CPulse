cmake_minimum_required(VERSION 3.10)
project(CPulse LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optionally, disable exceptions
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
    Classes/Enums/TokenTypes.cpp
    Classes/Structs/Token.h
    Classes/AST.h
    Classes/Parser.h
    Classes/Parser.cpp
    Classes/CodeGenerator.h
    Classes/CodeGenerator.cpp # Updated extension from .CPP to .cpp for consistency
 "Classes/Enums/VariableTypes.cpp")

# Include directories
include_directories("Classes" "Classes/Enums" "Classes/Structs")

# Optionally, to use the latest draft features with MSVC
if(MSVC)
    target_compile_options(CPulse PRIVATE "/std:c++latest")
endif()