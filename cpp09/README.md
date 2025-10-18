# C++ Module 09 - STL

This module focuses on using STL (Standard Template Library) containers and algorithms.

## Overview

The module contains three exercises that demonstrate the use of different STL containers:
- **Exercise 00**: Bitcoin Exchange (uses `std::map`)
- **Exercise 01**: Reverse Polish Notation Calculator (uses `std::stack`)
- **Exercise 02**: Merge-Insert Sort (uses `std::vector` and `std::deque`)

Each exercise uses different containers, and once a container is used, it cannot be reused in subsequent exercises.

---

## Exercise 00: Bitcoin Exchange

### Description
A program that calculates the value of a certain amount of bitcoin on a specific date using a CSV database.

### Usage
```bash
cd ex00
make
./btc input.txt
```

### Features
- Reads a CSV database of bitcoin prices over time
- Processes an input file with date | value format
- Validates dates (YYYY-MM-DD format)
- Validates values (0-1000 range)
- Uses the closest lower date if exact match not found
- Displays calculated results or appropriate error messages

### Container Used
- `std::map` - for storing and efficiently retrieving exchange rates by date

### Example
```bash
./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
```

---

## Exercise 01: Reverse Polish Notation (RPN)

### Description
A calculator that evaluates mathematical expressions in Reverse Polish Notation.

### Usage
```bash
cd ex01
make
./RPN "expression"
```

### Features
- Evaluates RPN expressions with numbers 0-9
- Supports operators: +, -, *, /
- Proper error handling for invalid expressions
- Stack-based evaluation

### Container Used
- `std::stack` - perfect for RPN evaluation (LIFO structure)

### Example
```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42

./RPN "7 7 * 7 -"
42

./RPN "1 2 * 2 / 2 * 2 4 - +"
0
```

---

## Exercise 02: PmergeMe

### Description
Implements the Ford-Johnson merge-insert sort algorithm using two different containers to compare performance.

### Usage
```bash
cd ex02
make
./PmergeMe [positive integers]
```

### Features
- Implements merge-insert sort (Ford-Johnson algorithm)
- Uses two different containers for comparison
- Handles at least 3000 different integers
- Measures and displays execution time for each container
- Validates input (positive integers only)

### Containers Used
- `std::vector` - dynamic array with contiguous memory
- `std::deque` - double-ended queue with segmented memory

### Example
```bash
./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 1 us
Time to process a range of 5 elements with std::deque : 5 us
```

### Algorithm Details
The Ford-Johnson algorithm combines:
1. **Pair sorting** - Sort elements in pairs
2. **Merge** - Combine sorted sequences
3. **Insertion** - Use insertion sort for small subarrays (threshold = 16)

This hybrid approach provides good performance by using merge sort's divide-and-conquer strategy for large datasets and insertion sort's efficiency for small datasets.

---

## Compilation

All exercises follow the same compilation rules:
- Compiler: `c++`
- Flags: `-Wall -Wextra -Werror -std=c++98`
- Each directory contains a Makefile with rules: `all`, `clean`, `fclean`, `re`

---

## Key Learning Points

1. **Container Selection**: Understanding when to use different STL containers based on their characteristics
   - `std::map`: O(log n) lookup, sorted by keys
   - `std::stack`: LIFO operations, O(1) push/pop
   - `std::vector`: Contiguous memory, fast random access
   - `std::deque`: Fast insertion/deletion at both ends

2. **Algorithm Implementation**: Implementing complex algorithms (Ford-Johnson) with standard containers

3. **Performance Analysis**: Comparing performance of different containers for the same task

4. **Error Handling**: Robust input validation and error reporting

5. **Orthodox Canonical Form**: All classes follow OCF (default constructor, copy constructor, assignment operator, destructor)

---

## Notes

- The project strictly follows C++98 standard
- No external libraries beyond the standard library
- Each exercise uses unique containers (no reuse across exercises)
- Memory management follows RAII principles
- Code is organized with header/implementation file separation
