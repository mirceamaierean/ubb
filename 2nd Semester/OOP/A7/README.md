# Assignment 07

Observation:
* Requirements **3** and **4** must be implemented using inheritance and polymorphism.

## Bonus possibility (0.2p, deadline week 9)
In addition to the file-based implementation for the repository, implement a true database-backed repository. For this, use inheritance and polymorphism. You are free to choose any type of database management system (e.g. `MySQL`, `SQLite`, `PostgreSQL`, `Couchbase` etc.).

## Problem Statement
For your solution to the previous assignments (Assignments 04-05, 06), add the following features:

1. Store data in a text file. When the program starts, entities are read from the file. Modifications made during program execution are stored in the file. Implement this using the `iostream` library. Create insertion and extraction operators for your entities and use these when reading/writing to files or the console.

2. Use exceptions to signal errors:
    - from the repository;
    - validation errors – validate your entities using Validator classes;
    - create your own exception classes.
    - validate program input.

3.	Depending on your assignment, store your (adoption list, movie watch list, shopping basket or tutorial watch list) in a file. When the application starts, the user should choose the type of file between `CSV` or `HTML`. Depending on the type, the application will save the list in the correct format.

    **Indications**\
    The CSV file will contain each entity on one line and the attributes will be separated by comma \
    The HTML file will contain a table, in which each row holds the data of one entity. The columns of the table will contain the names of the data attributes.\
    These are exemplified in the [example.csv](example.csv) and [example.html](example.html) files.
    `CSV` and `HTML` files are used to save and display data to the user; they act as program outputs, so data should not be read from them!

4. Add a new command, allowing the user to see the:
    * adoption list
    * movie watch list
    * shopping basket
    * tutorial watch list\
Displaying the list means opening the saved file (`CSV` or `HTML`) with the correct application (`CSV` files using Notepad, Notepad++, Microsoft Excel etc. and `HTML` files using a browser)

5. Create a UML class diagram for your entire application. For this, you can use any tool that you like ([StarUML](https://staruml.io/) or [LucidChart](https://www.lucidchart.com/) are only some examples. Many other options exist.
