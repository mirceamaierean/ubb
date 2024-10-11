# :computer: Assignment 06

## Requirements
- You will be given one of the problems below to solve
- In addition to **procedural programming**, also use **modular programming** by having a **UI** module, a **Functions** module and a **Start** module
- The **UI** module provides a command-based console user interface that accepts given commands **exactly** as stated
- Handle the case of incorrect user input by displaying error messages. The program must not crash regardless of user input.
- Use the built-in `list` or `dict` compound types to represent entities in the problem domain and access/modify them using *getter* and *setter* functions
- Use Python's [exception mechanism](https://docs.python.org/3/tutorial/errors.html) so that functions can signal that an exceptional situation, or error, has happened.
- Provide **specifications** for all non-UI functions (except getters and setters), and tests for all non-UI functions related to functionalities **(A)** and **(B)**
- Have at least 10 randomly generated items in your application at program startup
- Deadline for maximum grade is **week 8**, hard deadline is **week 11**.

## Problem Statements
### 5. Apartment Building Administrator
Jane is the administrator of an apartment building and she wants to manage the monthly expenses for each apartment. Each expense is stored using the following elements: `apartment` (*number of apartment, positive integer*), `amount` (*positive integer*), `type` (*from one of the predefined categories `water`, `heating`, `electricity`, `gas` and `other`*). Write a program that implements the functionalities exemplified below:

**(A) Add new transaction**\
`add <apartment> <type> <amount>`\
e.g.\
`add 25 gas 100` – add to apartment 25 an expense for `gas` in amount of `100 RON`

**(B) Modify expenses**\
`remove <apartment>`\
`remove <start apartment> to <end apartment>`\
`remove <type>`\
`replace <apartment> <type> with <amount>`\
e.g.\
`remove 15` – remove all expenses for apartment 15\
`remove 5 to 10` – remove all expenses for apartments between 5 and 10\
`remove gas` – remove all `gas` expenses from all apartments\
`replace 12 gas with 200` – replace the amount of the expense with type `gas` for apartment 12 with `200 RON`

**(C)	Display expenses having different properties**\
`list`\
`list <apartment>`\
`list [ < | = | > ] <amount>`\
e.g.\
`list` – display all expenses\
`list 15` – display all expenses for apartment 15\
`list > 100` - display all apartments having total expenses `>100 RON`\
`list = 17` - display all apartments having total expenses `=17 RON`

**(D) Filter**\
`filter <type>`\
`filter <value>`\
e.g.\
`filter gas` – keep only expenses for `gas`\
`filter 300` – keep only expenses having an amount of money smaller than 300 RON

**(E) Undo**\
`undo` – the last operation that modified program data is reversed. The user can undo all operations performed since program start by repeatedly calling this function.
