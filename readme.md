# CPSC-323 - Compilers & Languages

## Assignment 01 - LEXICAL ANALYZER
- By Cooper Santillan

----------------

### DUE DATES
Start Date | Time Due | Description
---------- | -------- | -----------
FEB 23, 2021 | @ Midnight | Extra Credit Due! Working iteration. No Documentation needed :)
MAR 02, 2021 | @ Midnight | Final Iteration. Documentation needed!
MAR 04, 2021 | @ Midnight | Latest Upload... (Late work)

---------------

### Build
This program utilizes a Makefile to build the program from the source code.
type `make` onto the terminal in order to build the executable. This will build a output file labeled `assignmentOne.o`.

in order to test whether this code is working, we can use one of the three example input files labeled:
1. **foo1.txt**
2. **foo2.txt**
3. **foo3.txt**

Here is an example of for if I would like the program to __print on STDOUT__:
`./assignmentOne foo1.txt`
`./assignmentOne foo2.txt`
`./assignmentOne foo3.txt`

Here is an example for if I would like the program to __print to a file__:
`./assignmentOne -o output1.txt foo1.txt`
`./assignmentOne -o output2.txt foo2.txt`
`./assignmentOne -o output3.txt foo3.txt`
and the content of these file would be found in a newly created files labeled: "output1.txt", "output2.txt", "output3.txt"

---------------

### ADVANTAGES:
The program everything as object in a doubly linked structure. This will come in handy later for later analyzers. The program also has the potential for operands to unlock special features; Hopefully to show the process. Program only accepts a certain input file extension; ensures that the user does accidently put the wrong file into program.

### LIMITATIONS:
This program will assume that anything that is not a keyword, seperator, operator, whole number, or a float is an identifier. Later, it should determine whether there is a valid identifier and mark when there are unknown tokens in the code. I also do not handle deleting heap memory. there is also a problem when typing something such as `./assignmentOne something` the program is terminated without a personal message. this is because the program assumes the last parameter in the executable is a file with an extension.

### SHORTCOMINGS:
Should inform the user if they are going to write to an output file that already exists. make a force flag if they want to skip prompt.