# CMakeList.txt : CMake project for CPulse, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CPulse "CPulse.cpp" "CPulse.h" "Classes/Lexer.cpp" "Classes/Lexer.h" "Classes/Enums/TokenTypes.h" "Classes/Enums/TokenTypes.cpp" "Classes/Structs/Token.h")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CPulse PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
