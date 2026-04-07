# string_exec

A console-based student record management system demonstrating structs, strings, and dynamic arrays.

## What it does

Implements a simple in-memory database of up to 10 student records with the following menu operations:

- **Add** a new student record (name + roll number, with duplicate roll number check)
- **Delete** a record by roll number
- **Display** all current records
- **Exit**

Each record is stored as a `StudentRecord` struct. The program validates input and prevents duplicate roll numbers.

## Concepts

- Structs with string fields (`char[]`)
- Passing structs by pointer to functions
- Linear search for lookup and duplicate detection
- Menu-driven program with `while(1)` loop and `switch`
- `string.h` functions (`strcpy`, `strcmp`)

## Environment

Host (PC) — compiled with GCC via STM32CubeIDE host toolchain.
