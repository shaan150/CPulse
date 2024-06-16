# README for CPulse

## Introduction
This guide provides an overview of the basic syntax and functionalities of your language, including variable declarations, control structures, function definitions, and list operations. It also highlights the type casting features and the dynamic nature of variable types. The main executable for the program is `CPulse.exe`.

## Prerequisites
- Visual Studio 2022
- CMake 3.16.5 or later
- Latest C++ runtime libraries

Ensure that these tools and libraries are installed on your system before attempting to build or run the program.

## Using the Program

### Running the Executable
To run the program, use the `CPulse.exe` executable located in the `out/build/x64-Release` or `out/build/Debug` directory depending on your build configuration.

**Important:**
- Ensure the `Files` directory is present in the same directory as `CPulse.exe`.
- The `Files` directory must contain `.txt` files following the specific syntax required by the language.

### Example Command to Run the Program
./CPulse.exe 

## Syntax and Features

### Variable Declarations
Variables can be declared and initialized using the `=` operator. The type of the variable is inferred from the assigned value. Variables are implicitly typed, meaning they can change types during execution, similar to Python.

is_running = true
shopping_list = list:string()
i = 0

### Global and Local Variables
Global Variables: Any variable declared outside of a function is a global variable and can be accessed from anywhere in the program.
Local Variables: Variables declared within a function are local to that function and cannot be accessed outside of it.

### Control Structures
While Loop
The while loop is used to execute a block of code as long as a specified condition is true.
(You can't just put variables by themselves, they require a Boolean)

while (is_running == true) {
    // Code to execute
}

If-Else Statements
if and else statements are used for conditional branching.

if (shopping_list.length() > 2) {
    // Code to execute if condition is true
} else {
    // Code to execute if condition is false
}


Functions
Functions are defined using the func keyword, followed by the return type, function name, and parameters. Note that functions do not support list types as parameters or return types.

func:int genItems(item:int) {
    test = item + 1
    print("genItems generated: " + test)
    return test
}

func:string test(item:string) {
    item_num = genItems(1)
    return "Processed " + item + item_num
}

Functions can be called by using their name followed by parentheses enclosing the arguments.

processed_item = test(item)


Lists
Lists can be declared and manipulated using methods like append, pop, replace, and indexing.

shopping_list = list:string()
shopping_list.append(item)
shopping_list.pop(int(itemToPop))
shopping_list.replace(0, "newItem")
item = shopping_list[0]
length = shopping_list.length()


Input and Output
Use the input function to get input from the user and the print function to output to the console. The input function requires an argument, which is the prompt displayed to the user.

item = input("Please add an item to the shopping list: ")
print("There's Too Many Items In This List")

Type Casting
Type casting is supported for all types except lists. You can cast values to int, string, double, and bool.
int_value = int("123")
string_value = string(123)
double_value = double("123.45")
bool_value = bool("true")


Example Program
is_running = true
shopping_list = list:string()
i = 0

while (is_running == true) {
    item = input("Please add an item to the shopping list: ")
    if (item == "") {
        is_running = false
    }
    shopping_list.append(item)
}

print(shopping_list)