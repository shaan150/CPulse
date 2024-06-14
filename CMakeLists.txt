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
    Classes/Enums/TokenType.h
    Classes/Enums/TokenType.cpp
    Classes/Structs/Token/Token.h
    Classes/AST.h
    "Classes/Parser/Parser.h"
    "Classes/Parser/Parser.cpp"
    Classes/CodeGenerator.h
    Classes/CodeGenerator.cpp # Updated extension from .CPP to .cpp for consistency
    
    Classes/Structs/Maps/OperatorMap.h
    Classes/Structs/Maps/KeywordMap.h 
     "Classes/Structs/Maps/KeywordMap.cpp" "Classes/Structs/Maps/OperatorMap.cpp" "Classes/Structs/ValueHelper.h"       "Classes/TypedVector.cpp"  "Classes/TypedVector.h" "Classes/Value.h"   "Classes/Evaluators/Primitive/PrimitiveNodeEvaluator.h" "Classes/Evaluators/Primitive/PrimitiveNodeEvaluator.cpp" "Classes/Evaluators/Variable/VariableNodeEvaluator.cpp" "Classes/Evaluators/Variable/VariableNodeEvaluator.h" "Classes/Evaluators/List/ListNodeEvaluator.h" "Classes/Evaluators/List/ListNodeEvaluator.cpp" "Classes/Evaluators/ControlFlow/ControlFlowEvaluator.h" "Classes/Evaluators/ControlFlow/ControlFlowEvaluator.cpp" "Classes/Evaluators/Expression/ExpressionNodeEvaluator.cpp" "Classes/Evaluators/Expression/ExpressionNodeEvaluator.h" "Classes/Evaluators/IO/IONodeEvaluator.h" "Classes/Evaluators/IO/IONodeEvaluator.cpp" "Classes/Evaluator.h" "Classes/Evaluator.cpp"  "Classes/Structs/Functions/Function.h" "Classes/Structs/Functions/FunctionContext.h" "Classes/Evaluators/Function/FunctionNodeEvaluator.h" "Classes/Evaluators/Function/FunctionNodeEvaluator.cpp" "Classes/Evaluators/Handler/FunctionHandler.h" "Classes/Evaluators/Handler/FunctionHandler.cpp" "Classes/Structs/Functions/Parameter.h" "Classes/Evaluators/Function/ReturnNodeEvaluator.h" "Classes/Evaluators/Function/ReturnNodeEvaluator.cpp")

# Include directories
include_directories("Classes" "Classes/Enums" "Classes/Structs")

# Optionally, to use the latest draft features with MSVC
if(MSVC)
    target_compile_options(CPulse PRIVATE "/std:c++latest")
endif()