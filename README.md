# 🎮 Wordle Game (C++ + SFML)

A graphical implementation of the classic Wordle game built using **C++** and the **SFML** (Simple and Fast Multimedia Library). This project was developed as a way to practice object-oriented design, GUI programming, file I/O, and C++ fundamentals.

---

## ✨ Features

- 🎨 Interactive graphical interface
- 🧠 Random word generation from answer list
- 🧾 Word validation from dictionary
- 🎹 On-screen keyboard with colored feedback
- 🧍‍♂️ Username input and leaderboard tracking
- 📊 Persistent scoring system

---

## 📁 Folder Structure

.
├── coding/
│ ├── main.cpp # Core game logic
│ ├── allwords.txt # Dictionary of valid guesses
│ ├── answers.txt # Answer bank to randomly choose from
│ ├── scores.txt # Stores usernames and scores
├── fonts/
│ ├── Roboto-Black.ttf # Primary game font
│ ├── Arial.ttf # Optional additional font
├── MakeFile # Build script to compile the game
├── .gitignore # Ignore compiled binaries and IDE files
├── README.md # Project documentation (this file)

---

## 🛠 Requirements

- **C++17** or higher
- **SFML 2.x** installed (graphics, window, and system modules)
- Compatible with Windows and Linux

To install SFML:
- [SFML Installation Guide](https://www.sfml-dev.org/tutorials/2.6/)

---

## 🧱 Build Instructions

### 🔧 Using the Provided Makefile

```bash
make        # Builds the project
./main      # Runs the game
