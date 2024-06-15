CPulse Guide

Introduction
This guide provides an overview of the basic syntax and functionalities of your language, including variable declarations, control structures, function definitions, and list operations. It also highlights the type casting features and the dynamic nature of variable types.

Syntax and Features
Variable Declarations
Variables can be declared and initialized using the = operator. The type of the variable is inferred from the assigned value. Variables are implicitly typed, meaning they can change types during execution, similar to Python.

is_running = true
shopping_list = list:string()
i = 0
Global and Local Variables
Global Variables: Any variable declared outside of a function is a global variable and can be accessed from anywhere in the program.
Local Variables: Variables declared within a function are local to that function and cannot be accessed outside of it.
Control Structures
While Loop
The while loop is used to execute a block of code as long as a specified condition is true.

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

plaintext
Copy code
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
Here is a complete example program demonstrating the usage of the features described above:

is_running = true
shopping_list = list:string()
i = 0

func:int genItems(item:int) {
    test = item + 1
    print("genItems generated: " + test)
    return test
}

func:string test(item:string) {
    item_num = genItems(1)
    return "Processed " + item + item_num
}

while (is_running == true) {
    if (shopping_list.length() > 2) {
        print("There's Too Many Items In This List, Please Remove 1 By Selecting The Number Next To The Item: ")
        i = 0
        while (i < shopping_list.length()) {
            print("Item: " + i)
            print("Item: " + shopping_list[i])
            i = i + 1
        }
        itemToPop = input("Please Remove The Item: ")
        shopping_list.pop(int(itemToPop))
    }

    item = input("Please add an item to the shopping list: ")

    if (item == "") {
        is_running = false
    }

    if (shopping_list.length() == 0) {
        shopping_list.append(item)
    } else {
        if (item != "") {
            processed_item = test(item)
            print(shopping_list.length())
            shopping_list.append(processed_item)
        }
    }
    i = i + 1
}

print(shopping_list)
Summary
This guide provides a basic overview of your language's syntax and features, including variable declarations, control structures, functions, lists, and I/O operations. It also covers type casting and the dynamic nature of variable types. Use this as a reference to understand the fundamental concepts and start writing programs in your language.

Additional Notes
Input: The input function requires an argument for the prompt.
List Operations: Use methods like append, pop, and replace for list manipulation. Indexing is supported using [], and the length of a list can be checked using .length.
Function Limitations: Functions do not support list types as parameters or return types.
Type Casting: Supported for int, string, double, and bool types, but not for lists.
Dynamic Typing: Variables are implicitly typed and can change types during execution.
