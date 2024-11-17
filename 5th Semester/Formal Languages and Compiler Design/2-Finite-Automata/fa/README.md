# Symbol Table and Lexical Analysis in Rust

This project implements a symbol table and lexical analysis tool in Rust, focusing on managing tokens, symbol table operations, and integrating finite automata to validate identifiers.

## Features

- **Symbol Table Implementation**:

  - Efficient insertion and retrieval of symbols using double hashing.
  - Dynamic resizing of the hash table for scalability.
  - Sorted output for displaying the symbol table.

- **Finite Automata Integration**:

  - Definition and parsing of states, alphabet, transitions, and final states.
  - Validation of strings using a deterministic finite automaton (DFA).

- **Lexical Token Processing**:
  - Identification of tokens (reserved words, constants, identifiers).
  - Validation of strings, integers, floats, and characters.
  - Error handling for invalid tokens.
- **File I/O**:
  - Reads token definitions, finite automata, and source code from input files.
  - Outputs a Program Internal Form (PIF) and the symbol table to files.

## Getting Started

### Prerequisites

- [Rust](https://www.rust-lang.org/tools/install) (version 1.65 or newer)

### Cloning the Repository

```bash
git clone <repository-url>
cd <project-folder>
```

### Building the Project

To build the project, run:

```bash
cargo build
```

### Running the Project

Run the program with the following usage:

```bash
cargo run <program.mm> <tokens.in> <fa.in>
```

- `<program.mm>`: File containing the source program to analyze.
- `<tokens.in>`: File containing the list of reserved tokens.
- `<fa.in>`: File defining the finite automata.

### Example

```bash
cargo run sample_program.mm tokens.in fa.in
```

### Outputs

- `pif.out`: Program Internal Form containing the parsed tokens.
- `st.out`: The generated symbol table.

## Project Structure

```plaintext
src/
├── file_reader.rs       # Handles file reading and parsing.
├── finite_automata.rs   # Defines and processes finite automata.
├── symbol_table.rs      # Implements the symbol table.
├── token_processor.rs   # Processes tokens using symbol table and finite automata.
├── main.rs              # Entry point of the application.
```

## Implementation Details

### Symbol Table

- **Hash Function**:

  - Double hashing for resolving collisions.
  - Primary hash: `first_hash`.
  - Secondary hash: `second_hash`.

- **Dynamic Resizing**:
  - Automatically doubles the capacity when the table is full.
  - Rehashes existing elements into the new table.

### Token Processor

- Recognizes the following token types:

  - Reserved words (from `tokens.in`).
  - Identifiers (validated via finite automata).
  - Constants: Strings, floats, and characters.

- Performs lexical analysis and outputs errors for invalid tokens.

### Finite Automata

Finite automata are mathematical models used for recognizing patterns and validating tokens. This project uses a deterministic finite automaton (DFA) to validate identifiers and tokens in the source code.

#### DFA Components:

- **States (Q)**: The finite set of states the automaton can be in. For example: `{q0, q1, q2, q3, q4, q5}`.
- **Alphabet (Σ)**: The set of symbols the DFA can process. For example: `{a, b, c, ..., z, 0, 1, ..., 9, _, -}`.
- **Initial State (q)**: The starting state of the automaton. For example: `q0`.
- **Transitions (δ)**: Rules that describe how the automaton moves between states based on input symbols. For example: `{(q0 _) = q1, (q0 0) = q2, (q0 123456789) = q3, (q3 0123456789) = q3, (q0 _abcdefghijklmnopqrstuvwxyz) = q4, (q4 _abcdefghijklmnopqrstuvwxyz0123456789) = q4}`.
- **Final States (F)**: States that indicate successful recognition of input. For example: `{q2, q3, q4}`.

#### DFA Representation in EBNF:

```ebnf
FiniteAutomata =
    "Q:" "{" States "}" ,
    "Σ:" "{" Alphabet "}" ,
    "q:" InitialState ,
    "δ:" "{" Transitions "}" ,
    "F:" "{" FinalStates "}" ;

States = State {"," State} ;
State = "q" Digit ;

Alphabet = Symbol {"," Symbol} ;
Symbol = Letter | Digit | "_" | "-" ;

InitialState = State ;

Transitions = Transition {"," Transition} ;
Transition = "(" State " " Symbols ")" "=" State ;
Symbols = Symbol {Symbol} ;

FinalStates = State {"," State} ;

Letter = "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "w" | "x" | "y" | "z" ;
Digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
```

This EBNF defines the structure of the `fa.in` file, capturing the DFA's components and transitions. The DFA is essential for validating token patterns, such as identifiers, during lexical analysis.

## Testing

The project includes unit tests for:

- Symbol table operations (e.g., insertion, retrieval).
- Token processing and validation.
- Finite automata parsing and validation.

To run tests:

```bash
cargo test
```

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgments

- [Rust Language Documentation](https://doc.rust-lang.org/)
- [Finite Automata Theory](https://en.wikipedia.org/wiki/Finite-state_machine)
