# Matrix & MataMvidia Modules 🎬

This project implements a ** matrix module ** and a ** movie navigation module ** as part of the **Introduction to System Programming** course (Technion, Spring 2024).  
It implements matrix operations and video frame management using C++.

---

## 📖 Overview

### Matrix Module
- Dynamic matrices with specified rows and columns.  
- Supports initialization, element access (read/write), and copying/assignment.  
- Arithmetic operations: addition (`+`), subtraction (`-`), multiplication (`*`).  
- Scalar multiplication, unary minus, comparison (`==`, `!=`).  
- Rotation (clockwise and counterclockwise) and transpose.  
- Formatted printing with vertical bars `|` around elements.  

### MataMvidia Module
- Represents a movie as a sequence of frames (each frame is a `Matrix`).  
- Stores metadata: movie name and author.  
- Supports frame access via indexing, concatenation of frames and movies.  
- Formatted printing of all frames with movie details.

---

## 🛠️ Tech Stack
- **C++17**  
- Object-oriented programming  
- Dynamic memory management  
- Operator overloading  
- Modular programming  
- No STL
  
---

## ⚙️ Usage

Compile and run the Matrix and MataMvidia modules:
```bash
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -o Mvidia wet/*.cpp
./Mvidia > test.out
diff --strip-trailing-cr -B -Z test.out wet/test.expected
```
