# Assignment 02-03

## Requirements
- Each student will be given one of the problems below.
- The solution must use the **C language**.
- The problem should be solved over 2 iterations, due `Week 3` and `Week 4`:

### Week 3
- Solve at least requirements **a** and **b**.
- The vector used in the repository can be statically allocated.

### Week 4
- Solve all problem requirements.
- Define a vector structure with specific operations using a dynamically allocated array.
- Use modular programming.
- Source code must be specified and include tests for all non-UI functions
- The program must not leak memory!
- Use a layered architecture for your application (domain, repository, controller, UI). User interface, domain and data access elements will be stored in different modules. The user interface module will only contain the user interface part.
- Have at least 10 entries available at application startup.
- Handle user input errors gracefully (replace program crashes with nice error messages :blush:).

## Bonus possibilities
1. Implement the following requirements using function pointers **[deadline: week 4, bonus: 0.1p]**:
    - For requirement **b**, add a different type of filtering (of your choice).
    - For requirement **c**, add descending sorting. The user should choose the type of sort and the program will show the list of entities accordingly.
2. Provide 2 different implementations for the undo/redo functionality: one using a list of operations (this approach is a precursor of the [Command design pattern](https://en.wikipedia.org/wiki/Command_pattern)) and one where each state of the repository is recorded (this approach is not unlike the [Memento design pattern](https://en.wikipedia.org/wiki/Memento_pattern)). Implement your dynamic array generically, such that it can contain any type of elements (use void*). Use this structure for your repository, as well as to implement both undo/redo functionalities **[deadline: week 5, bonus: 0.1p]**.

## Problem Statements

### Pharmacy
John is the administrator of the *“Smiles”* Pharmacy. He needs a software application to help him manage his pharmacy's medicine stocks. Each **Medicine** has the following attributes: `name`, `concentration`, `quantity` and `price`. John wants the application to help him in the following ways:\
**(a)** Add, delete or update a medicine. A medicine is uniquely identified by its name and concentration. If a product that already exists is added, its quantity will be updated (the new quantity is added to the existing one).\
**(b)** See all available medicines containing a given string (if the string is empty, all the available medicines will be considered), sorted ascending by medicine name.\
**(c)** See only those medicines that are in short supply (quantity less than `X` items, where the value of `X` is user-provided).\
**(d)** Provide multiple undo and redo functionality. Each step will undo/redo the previous operation performed by the user.