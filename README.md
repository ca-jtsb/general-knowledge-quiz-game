# General Knowledge Quiz Game

A text-based General Knowledge Quiz Game developed in C as a Machine Project for CCPROG2.  
The program allows administrators to manage quiz data and players to test their knowledge across multiple topics while tracking scores.

---

## Features

### Main Menu
- Manage Data (Admin)
- Play Quiz
- Exit Program

---

## Admin: Manage Data
Access-protected via password authentication with masked input.

**Functionalities:**
- Add quiz records with topic-based automatic question numbering
- Edit existing records (topic, question, choices, or answer)
- Delete quiz records with confirmation
- Import quiz data from a text file
- Export quiz data to a text file
- Return to Main Menu (clears in-memory data)

**Record Structure:**
- Topic  
- Question Number  
- Question  
- Choice 1  
- Choice 2  
- Choice 3  
- Correct Answer  

---

## Player: Quiz Game

**Options:**
- Play Quiz
- View Scores
- Exit to Main Menu

**Gameplay:**
- Player selects a topic per turn
- A random question is displayed from the chosen topic
- Score increases for every correct answer
- Scores are displayed in real time
- Player may end the game at any time

---

## Score System
- Scores are loaded from `score.txt` upon entering Play mode
- Updated scores are saved automatically before exiting
- Rankings are displayed with row number, player name, and score

---

## File Handling
- Quiz data and scores are stored using plain text files
- Import and export formats strictly follow the project specification
- Existing files are overwritten during export

---

## Technologies Used
- C Programming Language
- File I/O
- Arrays and Structures
- Modular Programming
- Git & GitHub for version control

---

## How to Run
1. Compile the program using a C compiler (e.g., GCC)
2. Run the executable in a terminal
3. Follow the on-screen menu instructions

---

## Notes
- Data persistence is handled only through exported files
- Admin password is hardcoded as required by the project specifications
