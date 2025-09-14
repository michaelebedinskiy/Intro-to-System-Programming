# TaskManager & SortedList 🗂️

This project implements a **generic sorted list** and a **task management system** in C++ as part of the Technion course *Introduction to System Programming* (234124, Spring 2024).

## 📖 Overview
- **SortedList**: generic container supporting insertion, removal, iteration, filtering, and applying functions while maintaining sorted order; supports duplicates and both const and non-const iterators.
- **TaskManager**: manages tasks assigned to employees with priority handling; supports adding, completing, and printing tasks by type or by employee.
- Uses exception handling to signal invalid operations (e.g., exceeding max employees, invalid task assignment).

## 🛠️ Tech Stack
- C++17
- Object-oriented design
- No STL containers
- Custom iterators, generic programming, exception handling

## 🚀 Running Tests
Compile:
```bash
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -Werror -o TaskManager *.cpp
```
Run all tests:
```bash
./TaskManager
```
Compare outputs:
```bash
diff --strip-trailing-cr -B -Z test1.out tests/test1.expected
```
