The Discrete Dungeon: Syllabus Quest (Final Edition)

Course: CSC101 Discrete Mathematics 


Institution: University of Engineering and Technology (UET), Lahore 


Teacher: Mr. Waqas Ali 

1. Project Description

The Discrete Dungeon is a professional C++ console-based educational game designed to reinforce the primary discrete mathematics concepts studied in the CSC101 curriculum. The game features five distinct "Tracks" that act as dungeon levels, each requiring the player to solve mathematical puzzles to progress.
+1

2. Mathematical Tracks Included
The game is structured according to the following syllabus tracks:

Track 1: Foundations of Logic – Truth tables, contrapositives, and argument validity.

Track 2: Discrete Structures – Set operations (Intersection/Union) and Power Set cardinality.

Track 3: Algorithm Design & Analysis – Binary search logic and Big-O time complexity.

Track 4: Number Theory Applications – Modular arithmetic and Caesar Cipher cryptography.

Track 5: Counting & Combinatorics – Product rule, combinations, and the Pigeonhole Principle.

3. Installation Instructions
Clone the Repository:

Bash

git clone https://github.com/[your-username]/[your-repo-name].git
Compile: Use any standard C++ compiler (GCC/MinGW).

Bash

g++ src/Project.cpp -o DungeonQuest
Run:

Bash

./DungeonQuest
4. Usage Examples
Navigation: Use the numeric keypad (1-5) to select a track from the main menu.

Unlocking: A track only becomes [OPEN] once the previous track has been [CLEARED].


Winning: You must answer at least 2 questions correctly per track to clear it.

5. Dependencies

Language: C++17.

System: Windows OS (specifically required for <windows.h> and SetConsoleTextAttribute for colors and typing effects).


Compiler: MinGW or any GCC-based compiler.

6. Project Structure
src/: Contains the main source code (Project.cpp).

test/: Contains test_cases.txt documenting logic verification.

data/: Contains syllabus_metadata.txt mapping game levels to course topics.
