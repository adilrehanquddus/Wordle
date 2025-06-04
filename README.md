🎮 Wordle Game (C++ + SFML)

A graphical implementation of the classic Wordle game built using C++ and the SFML (Simple and Fast Multimedia Library). This project was developed as a way to practice object-oriented design, GUI programming, file I/O, and C++ fundamentals.

✨ Features

🎨 Interactive graphical interface

🧠 Random word generation from answer list

🧾 Word validation from dictionary

🎹 On-screen keyboard with colored feedback

🧏‍♂️ Username input and leaderboard tracking

📊 Persistent scoring system

📁 Folder Structure

.

├── coding/

│   ├── main.cpp

│   ├── allwords.txt

│   ├── answers.txt

│   └── scores.txt

├── fonts/

│   ├── Roboto-Black.ttf

│   └── Arial.ttf

├── MakeFile

├── .gitignore

└── README.md


🛠 Requirements

C++17 or higher

SFML 2.x installed (graphics, window, and system modules)

Compatible with Windows and Linux

To install SFML:

SFML Installation Guide

🧱 Build Instructions

🔧 Using the Provided Makefile

make        # Builds the project
./main      # Runs the game

Make sure the SFML libraries are correctly linked and available in your system path or compilation setup.

🎙 Gameplay Instructions

Launch the game and enter your username

Try to guess the 5-letter word in 6 attempts

Letters are color-coded based on correctness:

🟩 Green = Correct letter and position

🟨 Yellow = Correct letter, wrong position

⬛ Gray = Letter not in word

If you win, your score is saved and averaged

View the leaderboard at the end

🧢 File Descriptions

answers.txt: List of correct answers (randomly selected)

allwords.txt: Full list of acceptable guesses

scores.txt: Stores scores in format score,username

💡 What I Learned

Handling window events and rendering with SFML

Managing game states and UI transitions

Validating user input and managing string data

Reading/writing structured data from text files

Organizing C++ code for clarity and extensibility

📜 License

This project is licensed under the MIT License. Feel free to fork, modify, and use as you wish!

🤛 Author

Made by Adil Rehan Quddus and Khadija Kazi
