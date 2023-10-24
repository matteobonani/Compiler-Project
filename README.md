# Flash

## Table of Contents

- [Introduction](#introduction)
- [Language Grammar Documentation](#language-grammar-documentation)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This project is a compiler for a programming language designed to perform arithmetic computations, handle conditional statements, and support variable declarations. The compiler consists of two main components: the lexer (implemented using Flex) and the parser (implemented using Yacc).

The goal of this project is to provide a language with a simplified syntax for arithmetic expressions, conditional statements, variable declarations, and basic input/output operations. 
We have introduced additional unique operations in the language, such as the "={DOUBLE}=" operator. This operator functions similarly to the "==" operator but with a double value for tolerance.
Another distinctive feature is the ability to convert strings like "ONE" to their corresponding integer value (from 0 to 9 only), such as 1, when performing basic operations.


## Language Grammar Documentation

### Syntax Rules

The following syntax rules define the grammar of the language:

- The starting point of the grammar is the `line` non-terminal.
- Statements can appear on a line, and multiple statements can be present on a single line.
- The `statement` non-terminal represents different types of statements in the language, such as exit, symbol table printing, variable assignment, conditional statements, and print statements.
- Expressions are built using the `expr` non-terminal and can involve numeric values, variables, strings, and various arithmetic operations.
- Conditions are constructed using the `conditions` non-terminal and can consist of comparisons between expressions using relational operators.
- Conditional blocks are formed with the `if_block` non-terminal and can include an optional `else_block`.
- Variable assignment is handled by the `assignment` non-terminal, allowing for assignments of integer, decimal, boolean, and string types.
- Boolean values are represented using the `boolean` non-terminal, which can be either `TRUE` or `FALSE`.

### Terminal Symbols

The grammar uses several terminal symbols, which include:

- `INT`: Integer value
- `DEC`: Decimal value
- `NAME`: Variable name
- `STRING`: String value
- `almost_equals`: Tolerance-based equality operator
- `symbols_table`: Symbol table printing keyword
- `strequals_nsens`: Case-insensitive string comparison operator
- `int_dec`: Integer variable declaration keyword
- `dec_dec`: Decimal variable declaration keyword
- `bool_dec`: Boolean variable declaration keyword
- `string_dec`: String variable declaration keyword
- `greater_equal`: Greater than or equal to operator
- `smaller_equal`: Smaller than or equal to operator
- `EQUALS`: Equality operator
- `TRUE`: Boolean true value
- `FALSE`: Boolean false value
- `PRINT`: Print statement keyword
- `IF`: If statement keyword
- `ELSE`: Else statement keyword
- `EXIT`: Exit statement keyword
- `;`: Statement terminator
- `+`, `-`, `*`, `/`: Arithmetic operators
- `power`: Exponentiation operator
- `(`, `)`: Parentheses for grouping expressions
- `{`, `}`: Curly braces for defining code blocks

### Non-Terminal Symbols

The grammar uses several non-terminal symbols, including:

- `line`: Represents a line of statements
- `expr`: Represents an expression
- `conditions`: Represents a condition for conditional statements
- `statement`: Represents various types of statements
- `if_block`: Represents an if statement block
- `else_block`: Represents an else statement block
- `conditional_block`: Represents a block of code within conditional statements
- `assignment`: Represents variable assignments
- `boolean`: Represents boolean values

### Operator Precedence

The grammar specifies the precedence of operators using `%left` directives. The order of precedence from highest to lowest is as follows:

- `power`
- `*`, `/`
- `+`, `-`
- Relational operators (`<`, `>`, `<=`, `>=`)
- Equality operators (`almost_equals`, `strequals_nsens`, `EQUALS`)

## Usage

To run the Compiler, please follow the steps outlined below:

1. Execute the Makefile to generate all the necessary files required for running the compiler. The Makefile contains all the commands required for this process.
```shell
    $ make
```
3. Run the compiler by executing the following command in your terminal:
```shell
    $ sudo ./compiler 
```

## Examples

An example usage of the Compiler is provided with the `test.txt` file. You can run the Compiler with this example file using the following command line:
```shell
    $ sudo ./compiler < test.txt
```

## Contributing

- Matteo Bonani 20011
- Alessio Eritale 20435

