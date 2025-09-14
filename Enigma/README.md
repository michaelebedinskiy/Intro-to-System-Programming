# Enigma Cipher 🔐

This project implements a simplified version of the **Enigma machine** in Python, developed as part of the Technion course *Introduction to System Programming* (Spring 2024).

## 📖 Overview
- Encrypts and decrypts text messages using configurable **wheels**, **hash maps**, and a **reflector map**.
- Includes wheel-advancement logic after each character (letters and non-letters).
- Supports reading configuration from JSON and restoring machine state.
- Provides a command-line interface (CLI) for running encryption as a script:
  ```bash
  python3 enigma.py -c config.json -i input.txt -o output.txt
  ```
-Handles errors gracefully with clear messages.
## 🛠️ Tech Stack
- Python 3.10+
- Object-oriented design (Enigma class)
- File handling and JSON parsing
- Exception handling and CLI argument parsing
## ✅ Testing
The project includes test inputs and expected outputs in the tests/ folder.
You can compare your program’s output with the expected result using:
```bash
diff --strip-trailing-cr -B -Z test1.out test1.expected
```
