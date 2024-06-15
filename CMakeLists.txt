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
    Classes/Lexer/Lexer.cpp
    Classes/Lexer/Lexer.h
    Classes/Enums/TokenType.h
    Classes/Enums/TokenType.cpp
    Classes/Structs/Token/Token.h
    "Classes/AST/AST.h"
    "Classes/Parser/Parser.h"
    "Classes/Parser/Parser.cpp"
    Classes/CodeGenerator/CodeGenerator.h
    Classes/CodeGenerator/CodeGenerator.cpp # Updated extension from .CPP to .cpp for consistency
    
    Classes/Structs/Map/OperatorMap.h
    Classes/Structs/Map/KeywordMap.h 
     "Classes/Structs/Map/KeywordMap.cpp" "Classes/Structs/Map/OperatorMap.cpp" "Classes/Structs/Value/ValueHelper.h"       "Classes/TypedVector/TypedVector.cpp"  "Classes/TypedVector/TypedVector.h" "Classes/Value/Value.h"   "Classes/CodeGenerator/Evaluator/Primitive/PrimitiveNodeEvaluator.h" "Classes/CodeGenerator/Evaluator/Primitive/PrimitiveNodeEvaluator.cpp" "Classes/CodeGenerator/Evaluator/Variable/VariableNodeEvaluator.cpp" "Classes/CodeGenerator/Evaluator/Variable/VariableNodeEvaluator.h" "Classes/CodeGenerator/Evaluator/List/ListNodeEvaluator.h" "Classes/CodeGenerator/Evaluator/List/ListNodeEvaluator.cpp" "Classes/CodeGenerator/Evaluator/ControlFlow/ControlFlowEvaluator.h" "Classes/CodeGenerator/Evaluator/ControlFlow/ControlFlowEvaluator.cpp" "Classes/CodeGenerator/Evaluator/Expression/ExpressionNodeEvaluator.cpp" "Classes/CodeGenerator/Evaluator/Expression/ExpressionNodeEvaluator.h" "Classes/CodeGenerator/Evaluator/IO/IONodeEvaluator.h" "Classes/CodeGenerator/Evaluator/IO/IONodeEvaluator.cpp" "Classes/CodeGenerator/Evaluator/Evaluator.h" "Classes/CodeGenerator/Evaluator/Evaluator.cpp"  "Classes/Function/Function.h" "Classes/Structs/Function/FunctionContext.h" "Classes/CodeGenerator/Evaluator/Function/FunctionNodeEvaluator.h" "Classes/CodeGenerator/Evaluator/Function/FunctionNodeEvaluator.cpp" "Classes/CodeGenerator/Evaluator/Handler/FunctionHandler.h" "Classes/CodeGenerator/Evaluator/Handler/FunctionHandler.cpp" "Classes/Structs/Function/Parameter.h" "Classes/CodeGenerator/Evaluator/Function/ReturnNodeEvaluator.h" "Classes/CodeGenerator/Evaluator/Function/ReturnNodeEvaluator.cpp" "Classes/Parser/Statement/StatementParser.h" "Classes/Parser/Statement/StatementParser.cpp" "Classes/Parser/Expression/ExpressionParser.h" "Classes/Parser/Expression/ExpressionParser.cpp" "Classes/Parser/Primary/PrimaryParser.h" "Classes/Parser/Primary/PrimaryParser.cpp" "Classes/CodeGenerator/Operation/ArithmeticOperations/ArithmeticOperations.h" "Classes/CodeGenerator/Operation/ArithmeticOperations/ArithmeticOperations.cpp" "Classes/CodeGenerator/Utility/PrintOperations.h" "Classes/CodeGenerator/Utility/PrintOperations.cpp" "Classes/CodeGenerator/Operation/UnaryOperations/UnaryOperations.h" "Classes/CodeGenerator/Operation/UnaryOperations/UnaryOperations.cpp" "Classes/CodeGenerator/Operation/StringOperations/StringOperations.h" "Classes/CodeGenerator/Operation/StringOperations/StringOperations.cpp" "Classes/CodeGenerator/Operation/OperationDispatcher/OperationDispatcher.h" "Classes/CodeGenerator/Operation/ComparisonOperations/ComparisonOperations.h" "Classes/CodeGenerator/Operation/ComparisonOperations/ComparisonOperations.cpp" "Classes/CodeGenerator/Operation/OperationDispatcher/OperationDispatcher.cpp" "Classes/CodeGenerator/Operation/LogicalOperations/LogicalOperations.h" "Classes/CodeGenerator/Operation/LogicalOperations/LogicalOperations.cpp")

# Include directories
include_directories("Classes" "Classes/Enums" "Classes/Structs")

# Optionally, to use the latest draft features with MSVC
if(MSVC)
    target_compile_options(CPulse PRIVATE "/std:c++latest")
endif()