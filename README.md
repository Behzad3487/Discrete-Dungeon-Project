# The Discrete Dungeon: Syllabus Quest (Final Edition)

**Course:** CSC101 Discrete Mathematics  
[cite_start]**Institution:** University of Engineering and Technology (UET), Lahore [cite: 5, 6]  
[cite_start]**Teacher:** Mr. Waqas Ali [cite: 15]

## 1. Project Description
[cite_start]**The Discrete Dungeon** is a C++ console-based educational game designed to reinforce primary discrete mathematics concepts[cite: 37, 38]. [cite_start]The game features five "Tracks" that act as dungeon levels, requiring players to solve mathematical puzzles to progress[cite: 29].

## 2. Mathematical Tracks Included
[cite_start]The game is structured according to the following syllabus tracks[cite: 30]:
* [cite_start]**Track 1: Foundations of Logic** – Truth tables, contrapositives, and argument validity[cite: 31].
* [cite_start]**Track 2: Discrete Structures** – Set operations and Power Set cardinality[cite: 32].
* [cite_start]**Track 3: Algorithm Design & Analysis** – Binary search logic and Big-O time complexity[cite: 33].
* [cite_start]**Track 4: Number Theory Applications** – Modular arithmetic and Caesar Cipher cryptography[cite: 35].
* [cite_start]**Track 5: Counting & Combinatorics** – Product rule and the Pigeonhole Principle[cite: 36].

## 3. Installation Instructions
1. **Clone the Repository:**
   [cite_start]`git clone https://github.com/Behzad3487/Discrete-Dungeon-Project` 
2. [cite_start]**Compile:** Use a standard C++ compiler[cite: 50, 55].
   `g++ src/Project.cpp -o DungeonQuest`
3. **Run:**
   `./DungeonQuest`

## 4. Usage Examples
* [cite_start]**Navigation:** Use numeric keys (1-5) to select a track[cite: 110].
* [cite_start]**Unlocking:** Tracks open sequentially; you must clear the previous level to proceed[cite: 113].
* [cite_start]**Winning:** Answer at least 2 questions correctly per track to clear it[cite: 121].

## 5. Dependencies
* [cite_start]**Language:** C++17[cite: 50].
* [cite_start]**System:** Windows OS (required for `<windows.h>` colors and effects)[cite: 55].
* [cite_start]**Compiler:** MinGW or GCC[cite: 55].

## 6. Project Structure
* `src/`: Contains the source code (`Project.cpp`).
* [cite_start]`test/`: Documents logic verification[cite: 117].
* [cite_start]`data/`: Maps game levels to course topics[cite: 58].
