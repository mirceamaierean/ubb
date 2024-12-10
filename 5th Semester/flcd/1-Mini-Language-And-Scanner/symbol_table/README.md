# SymbolTable

A Rust implementation of a simple `SymbolTable` using a custom hash table with double hashing for conflict resolution. This `SymbolTable` allows for efficient storage and retrieval of string keys associated with unique `usize` values. It is built to handle collisions and automatically resizes when the table becomes full.

## Overview

The `SymbolTable` struct contains:

- `hash`: A vector of `Option<(String, usize)>`, where `String` is the key, and `usize` represents a unique value for each key.
- `position`: The count of elements currently stored in the table, representing the next available index.

The `SymbolTable` uses a custom double-hashing strategy to avoid collisions. This means that when an initial hash position is occupied, a secondary hash function determines an alternate position.

### Key Methods

- **`new(capacity: Option<usize>) -> SymbolTable`**: Initializes a `SymbolTable` with a specified capacity or defaults to 16 slots if no capacity is provided.
- **`first_hash(&self, key: &String) -> usize`**: Generates the initial hash for a given key.
- **`second_hash(&self, key: &String) -> usize`**: Generates the secondary hash for a given key, used in double hashing.
- **`hash_function(&self, key: &String, pos: usize) -> usize`**: Combines `first_hash` and `second_hash` with `pos` (number of insertion attempts) to find a suitable slot.
- **`put(&mut self, item: (String, usize))`**: Inserts a key-value pair into the symbol table, expanding the table if necessary.
- **`rehash(&mut self)`**: Doubles the table's capacity and reinserts all elements to reduce collisions.
- **`insert(&mut self, key: String)`**: Inserts a key with a unique `usize` value.
- **`get(&self, key: String) -> Option<usize>`**: Retrieves the value associated with a key, or returns `None` if the key does not exist.

## Usage

### Sample Code

```rust
fn main() {
    let mut st = SymbolTable::new(Some(2));

    st.insert("hello".to_string());
    st.insert("world".to_string());
    st.insert("this".to_string());
    st.insert("is".to_string());
    st.insert("a".to_string());
    st.insert("test".to_string());

    // Retrieve values for inserted keys
    println!("{:?}", st.get("hello".to_string())); // Some(index)
    println!("{:?}", st.get("not".to_string()));   // None, if key doesn't exist

    // Print all key-value pairs
    st.hash.iter().for_each(|x| {
        if let Some(item) = x {
            println!("{:?}", item);
        }
    });
}
```
