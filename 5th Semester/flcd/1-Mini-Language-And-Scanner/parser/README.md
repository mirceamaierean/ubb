# Token Processor

This project is a lexical analysis tool written in Rust. It reads a source file, tokenizes it based on a set of predefined regular expressions, and outputs the resulting tokens along with their positions in a symbol table to a specified output file. The program identifies reserved tokens, operators, identifiers, and various types of constants (integers, floats, strings, and characters) according to custom-defined rules and patterns.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Code Structure](#code-structure)
- [Customization](#customization)
- [License](#license)

## Features

- **Token Classification**: Distinguishes between reserved words, operators, identifiers, integer and float constants, and string and character constants.
- **Symbol Table Management**: Manages a symbol table, storing each unique token and assigning an index.
- **Error Handling**: Detects and reports invalid tokens in the input file.
- **Customizable**: Easily configurable to recognize different reserved words and token patterns.

## Installation

1. Clone the repository.
2. Ensure that [Rust](https://www.rust-lang.org/tools/install) is installed.
3. In the project directory, run:

```bash
cargo build
```

## Usage

To run the program, use the following command:

```bash
cargo run tokens.in <program.mm>
```

- `tokens.in`: Path to a file containing the reserved tokens, one per line.
- `<program.mm>`: Path to the source code file to be tokenized.

Example:

```bash
cargo run reserved_tokens.txt my_program.mm
```

The output will be saved in a file named `pif.out` in the same directory, containing either a token's index from the symbol table or an error message if an invalid token was encountered.

## File Structure

- **`main.rs`**: Entry point of the program.
- **`symbol_table.rs`**: Symbol table module, used to store and retrieve token indices.
- **`tokens.in`**: Example file listing reserved tokens.
- **`program.mm`**: Example input file containing code to be tokenized.
- **`pif.out`**: Output file generated by the program.

## Code Structure

- **`TokenProcessor`**: Core struct handling token processing, symbol table management, and file output.
- **Regex Definitions**: Regular expressions to identify token types:
  - `separators_regex`: Matches separators (e.g., `(`, `)`, `{`, `}`, `,`, `;`).
  - `operators_regex_expression`: Matches operators (e.g., `+`, `-`, `*`, `/`, `=`, `<`, `>`).
  - `int_constant_regex`: Matches integer constants.
  - `float_constant_regex`: Matches float constants.
  - `identifier_regex`: Matches valid identifiers.
  - `string_constant_regex`: Matches string constants.
  - `char_constant_regex`: Matches character constants.

## Customization

- Modify `tokens.in` to add or change reserved words.
- Adjust regex definitions in `TokenProcessor` to accommodate additional token types or patterns.