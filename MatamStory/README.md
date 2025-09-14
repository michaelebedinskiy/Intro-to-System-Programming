# MatamStory 🎮
A turn-based fantasy game implemented in C++ as part of the Technion course *Introduction to System Programming* (Spring 2024).

## 📖 Overview
MatamStory is a simplified RPG game inspired by MapleStory. 
- 2–6 players.
- Turn-based combat against monsters and random events.
- Supports different character jobs (Warrior, Archer, Magician) and personalities (Responsible, Risk-taking).
- Includes leaderboards, combat resolution, and random events like merchants and solar eclipses.

## 🛠️ Tech Stack
- C++17
- STL containers, smart pointers
- Object-oriented design with design patterns (e.g., Factory, Strategy)
- UML-based planning

## ✨ Features
Extendable system — easy to add new jobs, monsters, or events.
Clear separation of design (dry.pdf) and implementation.
Tested with automated input/output comparisons.

## 🚀 Running the Game
Compile:
```bash
g++ --std=c++17 -o MatamStory -Wall -pedantic-errors -Werror -DNDEBUG *.cpp Events/*.cpp Players/*.cpp -I. -I./Players -I./Events
```
Run:
```bash
./MatamStory tests/test1.events tests/test1.players
```
