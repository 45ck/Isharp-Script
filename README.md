# Mouse Script
Mouse Script is a lightweight application built in C++ that allows users to create simple scripts to automate various tasks on their computer. These scripts can be created using a simple and intuitive language, and can be run with just a single command.

Please note that I no longer actively develop this project and have not done any development work on it since 2018. The latest release has only been tested on Windows operating systems 8 and 10 and may not work on other operating systems.

## Features
- Varibles: Mouse Script allows users to define and use variables in their scripts. Variables can store strings, integers, and other data types.
- Functions: Mouse Script supports the creation and execution of custom functions. Functions can accept arguments and return values, allowing for more complex scripts.
- Conditional statements: Mouse Script supports if statements and other conditional logic, allowing users to create scripts that can make decisions and take different actions based on different conditions.
- Loops: Mouse Script supports looping constructs, allowing users to execute code multiple times in a row.
- Input/Output: Mouse Script allows users to read input from the user, display output to the console, and interact with the user through dialog boxes.
- System commands: Mouse Script allows users to execute system commands and interact with the operating system.

## Getting started
To get started with Mouse Script, simply download the application and run it from the command line. You can then create a script using the supported language and run it with the run command, followed by the path to the script file.

Here is an example of a simple script that displays a message to the user and asks for their input:

```php
:Main
$using = "Console";
Print "Please enter your name ";
$name = Input;
Print "Your name is: ";
Echo $name;
Pause;
```

For more information on the language and its supported features, please see the documentation.

## Contributions
Mouse Script is an open-source project and contributions are welcome. If you have an idea for a new feature or have found a bug, please open an issue on the project's GitHub page.

## Installing Mouse Scrip
Installing Mouse Script is easy! Simply download the latest release from the releases page on the project's GitHub page. The release package includes both the Mouse Script application and the Mouse Script Editor, a tool for creating and editing Mouse Script scripts.

To install Mouse Script, simply extract the release package to a location on your computer and run the Mouse Script application. You can then use the Mouse Script Editor or the command line to create and run Mouse Script scripts.

Please note that Mouse Script is only supported on Windows operating systems 8 and 10 and may not work on other operating systems.
![image](https://user-images.githubusercontent.com/98618920/210666360-80850782-56a6-4bd3-9b24-343f71494677.png)

## Language Reference
### Variables
Variables in Mouse Script are defined using the $ symbol, followed by the variable name. For example:
```php
$myVariable = "Hello, world!";
```
Variables can be assigned values of any data type, such as strings and integers.
```php
$myString = "Hello, world!";
$myInt = 42;
```
String and integers automatically convert. To use booleans use "true"/"false" or 1/0

### Functions
Functions are blocks of code that can be defined and called by name. They can accept arguments and return values, allowing for more complex scripts.

#### Defining a function
```php
:functionName
  // code here
```

For example:
```php
:greet
  Echo "Hello, world!";
```

### Calling a function
To call a function, use the goto command followed by the name of the function. You can also pass arguments to the function by separating them with colons.

For example:
```php
goto greet;

// or

goto greet >> "John", "Doe";
```

### Returning a value
To return a value from a function, use the return command followed by the value you want to return.

For example:
```php
:add
  $a = $args[0];
  $b = $args[1];
  return $a + $b;
```

You can then use the returned value in your script by storing it in a variable.
```php
$result = goto add >> 2, 3;
Echo $result; // prints 5
Pause;
```

Accessing arguments
Inside a function, you can access the arguments passed to the function using the $args array. The first argument is at index 0, the second at index 1, and so on.

For example:
```php
:greet
  $name = $args[0];
  Echo "Hello, ";
  Print $name;
  Print " .";
  Pause;
```

### Main function/label
The :Main function, also known as the main label, is the starting point of every Mouse Script program. It is the first function that is executed when the script is run, and all other functions and labels in the script are called from within :Main.

```php
:Main
    // code to be executed when the script starts
```

It is mandatory to include a :Main function in every Mouse Script program. If a :Main function is not present, the script will not run.

Note: Labels in Mouse Script are denoted by a colon (:) followed by the label name. They are used to define functions and are called using the goto command.

## Looping using Functions
Mouse Script supports looping through the use of functions. Functions in Mouse Script are essentially blocks of code that can be executed multiple times by calling the function's name.

You can use the goto command within the function to create a loop. For example:
```php
:loop_function
  Echo "Hello, world!";
  goto loop_function;
```

This will create a loop that continuously prints "Hello, world!" to the console.

You can also use conditional statements within a function to create more complex loops. For example:
```php
:Main
  $using = "Console";
  $counter = 0;

:count_function
  $counter += 1;
  Print "Counter: ";
  Echo $counter;
  if $counter=10; goto done;
  goto count_function;
    
:done
  Echo "Done counting!";
  Pause;
  Exit;
```

This will create a loop that counts from 1 to 10, then prints "Done counting!" and exits the loop.


