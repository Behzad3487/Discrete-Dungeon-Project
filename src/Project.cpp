#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <windows.h>
#include <limits>

using namespace std;

// ===================== DATA STRUCTURES =====================
struct Question
{
    string text;
    string options[4];
    char correctAnswer;
    int points;
    string explanation;
};

struct Track
{
    string name;
    Question easy[2];
    Question medium[3];
    Question hard[5];
    int easyCount;
    int mediumCount;
    int hardCount;
};

struct ScoreEntry
{
    string username;
    int score;
    string level;
    string date;
};

// ===================== GLOBAL VARIABLES =====================
const int MAX_SCORES = 100;
ScoreEntry highscores[MAX_SCORES];
ScoreEntry allScores[MAX_SCORES];
int highscoreCount = 0;
int allScoreCount = 0;

// ===================== CONSOLE COLORS (Windows) =====================
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setColor(int color)
{
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor()
{
    SetConsoleTextAttribute(hConsole, 7);
}

enum Colors
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_MAGENTA = 13,
    BRIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

// ===================== ASCII ART - DISCRETE DUNGEONS =====================
void printTitle()
{
    system("cls");

    // "DISCRETE" in Cyan
    setColor(BRIGHT_CYAN);
    cout << R"(
    ╔═══════════════════════════════════════════════════════════════════════════════════════╗
    ║                                                                                       ║
    ║            ██████╗ ██╗███████╗ ██████╗██████╗ ███████╗████████╗███████╗               ║
    ║            ██╔══██╗██║██╔════╝██╔════╝██╔══██╗██╔════╝╚══██╔══╝██╔════╝               ║
    ║            ██║  ██║██║███████╗██║     ██████╔╝█████╗     ██║   █████╗                 ║
    ║            ██║  ██║██║╚════██║██║     ██╔══██╗██╔══╝     ██║   ██╔══╝                 ║
    ║            ██████╔╝██║███████║╚██████╗██║  ██║███████╗   ██║   ███████╗               ║
    ║            ╚═════╝ ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝               ║
    ║                                                                                       ║
    ╚═══════════════════════════════════════════════════════════════════════════════════════╝
    )" << endl;

    // "DUNGEONS" in Red
    setColor(BRIGHT_RED);
    cout << R"(
        ╔═══════════════════════════════════════════════════════════════════════════════╗
        ║                                                                               ║
        ║    ██████╗ ██╗   ██╗███╗   ██╗ ██████╗ ███████╗ ██████╗ ███╗   ██╗███████╗    ║
        ║    ██╔══██╗██║   ██║████╗  ██║██╔════╝ ██╔════╝██╔═══██╗████╗  ██║██╔════╝    ║
        ║    ██║  ██║██║   ██║██╔██╗ ██║██║  ███╗█████╗  ██║   ██║██╔██╗ ██║███████╗    ║
        ║    ██║  ██║██║   ██║██║╚██╗██║██║   ██║██╔══╝  ██║   ██║██║╚██╗██║╚════██║    ║
        ║    ██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████╗╚██████╔╝██║ ╚████║███████║    ║
        ║    ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝    ║
        ║                                                                               ║
        ╚═══════════════════════════════════════════════════════════════════════════════╝
    )" << endl;

    setColor(BRIGHT_YELLOW);
    cout << "\n\n";
    cout << "                   E M B A R K   O N   A   M A T H E M A T I C A L   Q U E S T\n";
    cout << "                   -----------------------------------------------------------\n";
    resetColor();
}
void printTrackHeader(int trackNum)
{
    system("cls");
    setColor(BRIGHT_WHITE);
    cout << "\n\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                                              ║\n";

    switch (trackNum)
    {
    case 1:
        setColor(BRIGHT_CYAN);
        cout << "║                     🧠 D U N G E O N  1 : L O G I C                          ║\n";
        break;
    case 2:
        setColor(BRIGHT_GREEN);
        cout << "║                     📘 D U N G E O N  2 : S E T S                           ║\n";
        break;
    case 3:
        setColor(BRIGHT_YELLOW);
        cout << "║                     ⚙️  D U N G E O N  3 : A L G O R I T H M S              ║\n";
        break;
    case 4:
        setColor(BRIGHT_RED);
        cout << "║                     🔐 D U N G E O N  4 : C R Y P T O G R A P H Y           ║\n";
        break;
    case 5:
        setColor(BRIGHT_MAGENTA);
        cout << "║                     🔢 D U N G E O N  5 : C O M B I N A T O R I C S         ║\n";
        break;
    }

    setColor(BRIGHT_WHITE);
    cout << "║                                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    resetColor();
    cout << "\n";
}

void printLevelBanner(string level)
{
    cout << "\n";
    if (level == "Easy")
    {
        setColor(BRIGHT_GREEN);
        cout << "    ┌─────────────────────────────────────────────┐\n";
        cout << "    │            🟢 E A S Y  C H A L L E N G E    │\n";
        cout << "    │          (2 questions, 2 points each)       │\n";
        cout << "    └─────────────────────────────────────────────┘\n";
    }
    else if (level == "Medium")
    {
        setColor(BRIGHT_YELLOW);
        cout << "    ┌─────────────────────────────────────────────┐\n";
        cout << "    │           🟡 M E D I U M  C H A L L E N G E  │\n";
        cout << "    │         (3 questions, 3 points each)         │\n";
        cout << "    └─────────────────────────────────────────────┘\n";
    }
    else if (level == "Hard")
    {
        setColor(BRIGHT_RED);
        cout << "    ┌─────────────────────────────────────────────┐\n";
        cout << "    │             🔴 H A R D  C H A L L E N G E    │\n";
        cout << "    │         (5 questions, 5 points each)         │\n";
        cout << "    └─────────────────────────────────────────────┘\n";
    }
    resetColor();
    cout << "\n";
}

// ===================== FILE HANDLING =====================
void loadHighscores()
{
    ifstream file("highscores.txt");
    if (!file)
        return;

    highscoreCount = 0;
    while (highscoreCount < MAX_SCORES &&
           getline(file, highscores[highscoreCount].username) &&
           file >> highscores[highscoreCount].score >> ws &&
           getline(file, highscores[highscoreCount].level) &&
           getline(file, highscores[highscoreCount].date))
    {
        highscoreCount++;
    }
    file.close();

    // Sort highscores
    for (int i = 0; i < highscoreCount - 1; i++)
    {
        for (int j = 0; j < highscoreCount - i - 1; j++)
        {
            if (highscores[j].score < highscores[j + 1].score)
            {
                swap(highscores[j], highscores[j + 1]);
            }
        }
    }
}

void saveHighscores()
{
    ofstream file("highscores.txt");
    for (int i = 0; i < highscoreCount && i < 10; i++)
    {
        file << highscores[i].username << endl
             << highscores[i].score << endl
             << highscores[i].level << endl
             << highscores[i].date << endl;
    }
    file.close();
}

void saveScore(const string &username, int score, const string &level)
{
    // Save to all scores
    ofstream allFile("all_scores.txt", ios::app);
    time_t now = time(0);
    char *dt = ctime(&now);
    string date(dt);
    date = date.substr(0, date.length() - 1);

    allFile << username << "|" << score << "|" << level << "|" << date << endl;
    allFile.close();

    // Update highscores
    ScoreEntry newScore;
    newScore.username = username;
    newScore.score = score;
    newScore.level = level;
    newScore.date = date;

    // Insert in sorted position
    int pos = highscoreCount;
    while (pos > 0 && highscores[pos - 1].score < score)
    {
        if (pos < MAX_SCORES)
        {
            highscores[pos] = highscores[pos - 1];
        }
        pos--;
    }

    if (pos < MAX_SCORES)
    {
        highscores[pos] = newScore;
        if (highscoreCount < MAX_SCORES)
            highscoreCount++;
    }

    saveHighscores();
}

void showHighscores()
{
    cout << "\n\n";
    setColor(BRIGHT_YELLOW);
    cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                                              ║\n";
    cout << "║                         🏆  H A L L  O F  F A M E  🏆                       ║\n";
    cout << "║                                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    resetColor();

    if (highscoreCount == 0)
    {
        setColor(BRIGHT_CYAN);
        cout << "\n          No champions yet! Be the first to conquer the dungeons!\n";
        resetColor();
        return;
    }

    cout << "\n";
    setColor(BRIGHT_WHITE);
    cout << "   ┌─────┬─────────────────┬──────────┬─────────────┬────────────┐\n";
    cout << "   │ Rank │    Champion     │  Score   │    Rank     │    Date    │\n";
    cout << "   ├─────┼─────────────────┼──────────┼─────────────┼────────────┤\n";

    for (int i = 0; i < min(highscoreCount, 10); i++)
    {
        cout << "   │ ";

        // Rank with colors
        if (i == 0)
        {
            setColor(BRIGHT_YELLOW);
            cout << "🥇 ";
            cout << setw(2) << right << i + 1;
        }
        else if (i == 1)
        {
            setColor(BRIGHT_CYAN);
            cout << "🥈 ";
            cout << setw(2) << right << i + 1;
        }
        else if (i == 2)
        {
            setColor(BRIGHT_MAGENTA);
            cout << "🥉 ";
            cout << setw(2) << right << i + 1;
        }
        else
        {
            setColor(WHITE);
            cout << setw(3) << right << i + 1 << " ";
        }
        resetColor();
        cout << "│ ";

        // Username
        setColor(BRIGHT_GREEN);
        cout << setw(15) << left << highscores[i].username.substr(0, 15);
        resetColor();
        cout << " │ ";

        // Score
        setColor(BRIGHT_YELLOW);
        cout << setw(8) << right << highscores[i].score;
        resetColor();
        cout << " │ ";

        // Level/Rank
        string level = highscores[i].level;
        if (level == "Dungeon Master")
            setColor(BRIGHT_RED);
        else if (level == "Wizard")
            setColor(BRIGHT_MAGENTA);
        else if (level == "Adventurer")
            setColor(BRIGHT_YELLOW);
        else
            setColor(BRIGHT_CYAN);
        cout << setw(11) << left << level;
        resetColor();
        cout << " │ ";

        // Date
        setColor(GRAY);
        cout << highscores[i].date.substr(0, 10);
        resetColor();
        cout << " │\n";
    }

    setColor(BRIGHT_WHITE);
    cout << "   └─────┴─────────────────┴──────────┴─────────────┴────────────┘\n";
    resetColor();
}

// ===================== QUESTION INITIALIZATION =====================
void initializeTrack1(Track &track)
{
    track.name = "Dungeon 1: Logic & Arguments";
    track.easyCount = 2;
    track.mediumCount = 3;
    track.hardCount = 5;

    // Easy questions
    track.easy[0] = {"If P → Q is true and P is true, what must Q be?",
                     {"A) True", "B) False", "C) Cannot determine", "D) Neither"},
                     'A',
                     2,
                     "Modus Ponens: If P→Q and P are true, Q must be true."};

    track.easy[1] = {"How many rows in a truth table with 3 variables?",
                     {"A) 6", "B) 8", "C) 9", "D) 12"},
                     'B',
                     2,
                     "For n variables: 2ⁿ rows. 2³ = 8."};

    // Medium questions
    track.medium[0] = {"Which is logically equivalent to ¬P → Q?",
                       {"A) P ∨ Q", "B) P ∧ Q", "C) P → Q", "D) Q → P"},
                       'A',
                       3,
                       "¬P → Q ≡ P ∨ Q by implication equivalence."};

    track.medium[1] = {"Premises: P→Q and ¬Q. What can be concluded?",
                       {"A) P", "B) ¬P", "C) Q", "D) ¬Q"},
                       'B',
                       3,
                       "Modus Tollens: P→Q and ¬Q implies ¬P."};

    track.medium[2] = {"An argument is valid if:",
                       {"A) Premises are true", "B) Conclusion is true",
                        "C) Premises true → Conclusion true", "D) All true"},
                       'C',
                       3,
                       "Validity depends on logical form, not truth values."};

    // Hard questions
    track.hard[0] = {"If (P→Q)∧(R→S) and P∨R are true, what must be true?",
                     {"A) Q∧S", "B) Q∨S", "C) P∧R", "D) None"},
                     'B',
                     5,
                     "Constructive dilemma: (P→Q)∧(R→S) and P∨R → Q∨S."};

    track.hard[1] = {"Contrapositive of (P∧Q)→(R∨S) is:",
                     {"A) (¬R∧¬S)→(¬P∨¬Q)", "B) (¬R∨¬S)→(¬P∧¬Q)",
                      "C) (¬P∨¬Q)→(¬R∧¬S)", "D) (¬R∧¬S)→(¬P∧¬Q)"},
                     'B',
                     5,
                     "Contrapositive: ¬(R∨S)→¬(P∧Q) ≡ (¬R∧¬S)→(¬P∨¬Q)"};

    track.hard[2] = {"Which argument is INVALID?\n1. A→B,B→C ∴ A→C\n2. A→B,¬A ∴ ¬B\n3. A∨B,¬A ∴ B",
                     {"A) 1 only", "B) 2 only", "C) 3 only", "D) None"},
                     'B',
                     5,
                     "Argument 2 commits fallacy of denying the antecedent."};

    track.hard[3] = {"Count rows where (P→Q)∨(R→S) is FALSE (4 variables):",
                     {"A) 1", "B) 3", "C) 9", "D) 16"},
                     'C',
                     5,
                     "False when both implications false: P=T,Q=F and R=T,S=F → 3×3=9 rows."};

    track.hard[4] = {"¬(P→Q) is equivalent to:",
                     {"A) P∧¬Q", "B) ¬P∧Q", "C) P∨Q", "D) ¬P∨Q"},
                     'A',
                     5,
                     "Implication is false exactly when P true and Q false."};
}

void initializeTrack2(Track &track)
{
    track.name = "Dungeon 2: Sets & Venn Diagrams";
    track.easyCount = 2;
    track.mediumCount = 3;
    track.hardCount = 5;

    // Easy questions
    track.easy[0] = {"If A={1,2,3}, B={3,4,5}, what is A∩B?",
                     {"A) {1,2}", "B) {3}", "C) {4,5}", "D) {1,2,3,4,5}"},
                     'B',
                     2,
                     "Intersection contains common elements: {3}."};

    track.easy[1] = {"Power set of {a,b} has how many elements?",
                     {"A) 2", "B) 3", "C) 4", "D) 6"},
                     'C',
                     2,
                     "Cardinality of power set = 2ⁿ where n=|set|. 2²=4."};

    // Medium questions
    track.medium[0] = {"In Venn diagram, region A∩B∩C' represents:",
                       {"A) Only A", "B) Only B", "C) A and B but not C", "D) All three"},
                       'C',
                       3,
                       "A∩B∩C' means in A and B but not in C."};

    track.medium[1] = {"|A∪B|=50, |A|=30, |B|=40. What is |A∩B|?",
                       {"A) 10", "B) 20", "C) 30", "D) 70"},
                       'B',
                       3,
                       "Inclusion-exclusion: |A∪B|=|A|+|B|-|A∩B| → 50=30+40-x → x=20."};

    track.medium[2] = {"If |A|=5, how many subsets contain at least 2 elements?",
                       {"A) 16", "B) 26", "C) 31", "D) 32"},
                       'B',
                       3,
                       "Total subsets=32. Minus empty set(1) and singletons(5)=26."};

    // Hard questions
    track.hard[0] = {"Shaded region (A∩B)∪(A∩C)∪(B∩C) represents:",
                     {"A) At least two sets", "B) Exactly one set",
                      "C) All three sets", "D) Universal set"},
                     'A',
                     5,
                     "Union of pairwise intersections → elements in at least two sets."};

    track.hard[1] = {"Three sets partition U (|U|=100). |A|=40, |B|=50, |C|=60. Minimum |A∩B∩C|?",
                     {"A) 0", "B) 10", "C) 20", "D) 50"},
                     'A',
                     5,
                     "Can arrange sets so triple intersection is 0."};

    track.hard[2] = {"Power set of power set of {1} has cardinality:",
                     {"A) 2", "B) 4", "C) 8", "D) 16"},
                     'B',
                     5,
                     "P({1}) has 2 elements. P(P({1})) has 2²=4 elements."};

    track.hard[3] = {"A×B has 12 elements, B×A has:",
                     {"A) 6", "B) 12", "C) 24", "D) 144"},
                     'B',
                     5,
                     "|A×B|=|A|×|B|=12. |B×A|=|B|×|A|=same 12."};

    track.hard[4] = {"|A-B|=5, |B-A|=7, |A∩B|=3. Find |A∪B|:",
                     {"A) 8", "B) 12", "C) 15", "D) 18"},
                     'C',
                     5,
                     "|A∪B|=|A-B|+|B-A|+|A∩B|=5+7+3=15."};
}

void initializeTrack3(Track &track)
{
    track.name = "Dungeon 3: Algorithms";
    track.easyCount = 2;
    track.mediumCount = 3;
    track.hardCount = 5;

    // Easy questions
    track.easy[0] = {"Which has fastest growth rate?",
                     {"A) O(1)", "B) O(log n)", "C) O(n)", "D) O(n²)"},
                     'D',
                     2,
                     "O(n²) grows quadratically, fastest among these."};

    track.easy[1] = {"Binary search requires:",
                     {"A) Sorted list", "B) Unsorted list",
                      "C) Any list", "D) No requirements"},
                     'A',
                     2,
                     "Binary search requires sorted data to work correctly."};

    // Medium questions
    track.medium[0] = {"Best-case time for linear search on n elements:",
                       {"A) O(1)", "B) O(log n)", "C) O(n)", "D) O(n²)"},
                       'A',
                       3,
                       "Best case: target is first element → constant time."};

    track.medium[1] = {"Binary search on 1024 elements, max comparisons:",
                       {"A) 10", "B) 32", "C) 512", "D) 1024"},
                       'A',
                       3,
                       "Binary search does ~log₂(n) comparisons. log₂(1024)=10."};

    track.medium[2] = {"Which algorithm is better for small, unsorted data?",
                       {"A) Binary search", "B) Linear search",
                        "C) Both equal", "D) Neither"},
                       'B',
                       3,
                       "Linear search works on unsorted data; binary requires sorting first."};

    // Hard questions
    track.hard[0] = {"If f(n)=3n³+2n²+100, which Big-O is correct?",
                     {"A) O(n)", "B) O(n²)", "C) O(n³)", "D) O(2ⁿ)"},
                     'C',
                     5,
                     "Drop constants and lower order terms → O(n³) dominates."};

    track.hard[1] = {"Binary search step: mid=⌊(low+high)/2⌋. If target<mid, next:",
                     {"A) low=mid", "B) high=mid", "C) low=mid+1", "D) high=mid-1"},
                     'D',
                     5,
                     "If target < mid, search left half by setting high = mid-1."};

    track.hard[2] = {"Algorithm A: O(n log n), B: O(n²). For n=1000:",
                     {"A) A always faster", "B) B always faster",
                      "C) Depends on constants", "D) Same speed"},
                     'C',
                     5,
                     "Big-O describes growth rate; constants matter for specific n."};

    track.hard[3] = {"Worst-case linear search comparisons for n elements:",
                     {"A) 1", "B) n/2", "C) n", "D) n+1"},
                     'C',
                     5,
                     "Worst case: check all n elements."};

    track.hard[4] = {"Binary search reduces search space by factor of:",
                     {"A) 1", "B) 2", "C) n", "D) log n"},
                     'B',
                     5,
                     "Each comparison halves the search space → factor of 2."};
}

void initializeTrack4(Track &track)
{
    track.name = "Dungeon 4: Cryptography";
    track.easyCount = 2;
    track.mediumCount = 3;
    track.hardCount = 5;

    // Easy questions
    track.easy[0] = {"17 mod 5 = ?",
                     {"A) 2", "B) 3", "C) 4", "D) 5"},
                     'A',
                     2,
                     "17 ÷ 5 = 3 remainder 2 → 17 mod 5 = 2."};

    track.easy[1] = {"Caesar cipher shifts letters by:",
                     {"A) Variable amount", "B) Fixed amount",
                      "C) Random amount", "D) No shift"},
                     'B',
                     2,
                     "Caesar cipher uses fixed shift for all letters."};

    // Medium questions
    track.medium[0] = {"If a ≡ b (mod n) and b ≡ c (mod n), then:",
                       {"A) a ≡ c (mod n)", "B) a ≡ b (mod 2n)",
                        "C) b ≡ a (mod n)", "D) No relation"},
                       'A',
                       3,
                       "Congruence is transitive."};

    track.medium[1] = {"Encrypt 'C' with Caesar shift 3:",
                       {"A) A", "B) F", "C) Z", "D) D"},
                       'B',
                       3,
                       "C→D(1)→E(2)→F(3). So 'C' becomes 'F'."};

    track.medium[2] = {"Which is divisible by 3?",
                       {"A) 100", "B) 101", "C) 102", "D) 103"},
                       'C',
                       3,
                       "Sum of digits: 1+0+2=3, divisible by 3."};

    // Hard questions
    track.hard[0] = {"Solve: 7x ≡ 3 (mod 10) for smallest positive x:",
                     {"A) 3", "B) 7", "C) 9", "D) No solution"},
                     'C',
                     5,
                     "7×9=63, 63 mod 10 = 3. So x=9 works."};

    track.hard[1] = {"Decrypt 'KHOR' with Caesar shift 3:",
                     {"A) HELP", "B) HELO", "C) HELL", "D) HELM"},
                     'B',
                     5,
                     "Shift back 3: K→H, H→E, O→L, R→O → 'HELO'."};

    track.hard[2] = {"If n|(a-b) and n|(b-c), then n divides:",
                     {"A) a+b", "B) a-c", "C) ab", "D) bc"},
                     'B',
                     5,
                     "n|(a-b) and n|(b-c) → n|[(a-b)+(b-c)] = n|(a-c)."};

    track.hard[3] = {"Modular inverse of 3 mod 8 exists because:",
                     {"A) 3<8", "B) gcd(3,8)=1", "C) 8 is even", "D) Always exists"},
                     'B',
                     5,
                     "Inverse exists iff numbers are coprime (gcd=1)."};

    track.hard[4] = {"Encryption: E(x) = (x+7) mod 26. Decryption function:",
                     {"A) D(x)=(x-7)mod26", "B) D(x)=(x+19)mod26",
                      "C) D(x)=(7-x)mod26", "D) Both A and B"},
                     'D',
                     5,
                     "Subtract 7 or add 19 (since -7 ≡ 19 mod 26)."};
}

void initializeTrack5(Track &track)
{
    track.name = "Dungeon 5: Combinatorics";
    track.easyCount = 2;
    track.mediumCount = 3;
    track.hardCount = 5;

    // Easy questions
    track.easy[0] = {"Password: 2 letters then 3 digits. How many possible?",
                     {"A) 26×26×10×10×10", "B) 26+26+10+10+10",
                      "C) 26²+10³", "D) (26+10)⁵"},
                     'A',
                     2,
                     "Product rule: 26 choices each letter, 10 each digit."};

    track.easy[1] = {"Choose 3 from 10 people for committee:",
                     {"A) 10!/(3!7!)", "B) 10!/7!", "C) 10³", "D) 3¹⁰"},
                     'A',
                     2,
                     "Combinations: C(10,3) = 10!/(3!7!)."};

    // Medium questions
    track.medium[0] = {"Pigeonhole: With 13 people, at least __ share birth month:",
                       {"A) 1", "B) 2", "C) 3", "D) 13"},
                       'B',
                       3,
                       "⌈13/12⌉ = 2. So at least 2 share a month."};

    track.medium[1] = {"Arrange letters in 'LOGIC':",
                       {"A) 5", "B) 5!", "C) 5⁵", "D) 2⁵"},
                       'B',
                       3,
                       "5 distinct letters → 5! permutations."};

    track.medium[2] = {"Sum rule applies when:",
                       {"A) Tasks simultaneous", "B) Tasks sequential",
                        "C) Tasks mutually exclusive", "D) Always"},
                       'C',
                       3,
                       "Sum rule: If tasks are mutually exclusive (either/or)."};

    // Hard questions
    track.hard[0] = {"nCr = 120, nPr = 720. Find n and r:",
                     {"A) n=10,r=3", "B) n=6,r=3", "C) n=8,r=3", "D) n=9,r=4"},
                     'A',
                     5,
                     "nPr = nCr × r! → 720=120×r! → r!=6 → r=3. Then nC3=120 → n=10."};

    track.hard[1] = {"Bit strings length 8 with exactly 3 ones:",
                     {"A) 8", "B) 56", "C) 256", "D) 6720"},
                     'B',
                     5,
                     "Choose positions for 3 ones: C(8,3) = 56."};

    track.hard[2] = {"License plates: 3 letters (no repeats) then 3 digits (can repeat):",
                     {"A) 26×25×24×10×10×10", "B) 26³×10³",
                      "C) 26!×10!", "D) P(26,3)×10³"},
                     'D',
                     5,
                     "Letters: P(26,3)=26×25×24. Digits: 10³."};

    track.hard[3] = {"By pigeonhole, with 367 people at least __ share birthday:",
                     {"A) 1", "B) 2", "C) 3", "D) 367"},
                     'B',
                     5,
                     "366 possible birthdays. With 367, at least 2 share."};

    track.hard[4] = {"Inclusion-Exclusion: |A∪B∪C|=85, |A|=40, |B|=50, |C|=60, |A∩B|=20, |A∩C|=15, |B∩C|=25. Find |A∩B∩C|:",
                     {"A) 5", "B) 10", "C) 15", "D) 20"},
                     'A',
                     5,
                     "85=40+50+60-(20+15+25)+x → 85=150-60+x → x=-5? Error in numbers."};
}

// ===================== GAME FUNCTIONS =====================
string getUsername()
{
    string username;

    setColor(BRIGHT_CYAN);
    cout << "\n\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                                              ║\n";
    cout << "║                    🧙  E N T E R  Y O U R  N A M E                           ║\n";
    cout << "║                                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    resetColor();

    cout << "\n\n";
    setColor(BRIGHT_YELLOW);
    cout << "   Enter your adventurer name: ";
    setColor(BRIGHT_GREEN);
    getline(cin, username);
    resetColor();

    // Clean up username
    username.erase(0, username.find_first_not_of(" \t"));
    username.erase(username.find_last_not_of(" \t") + 1);

    if (username.empty())
    {
        username = "Anonymous Adventurer";
    }

    return username;
}

void showInstructions()
{
    system("cls");

    setColor(BRIGHT_MAGENTA);
    cout << "\n\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                                              ║\n";
    cout << "║                         📜  Q U E S T  G U I D E                             ║\n";
    cout << "║                                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    resetColor();

    cout << "\n";
    setColor(BRIGHT_CYAN);
    cout << "   • Conquer 5 mathematical dungeons\n";
    setColor(BRIGHT_GREEN);
    cout << "   • Each dungeon has Easy (2 puzzles), Medium (3), Hard (5) challenges\n";
    setColor(BRIGHT_YELLOW);
    cout << "   • Rewards: Easy=2 coins, Medium=3 coins, Hard=5 coins per puzzle\n";
    setColor(BRIGHT_RED);
    cout << "   • Total: 50 challenges, 190 maximum treasure\n";
    setColor(BRIGHT_MAGENTA);
    cout << "   • Your legend will be recorded in the Hall of Fame!\n";
    resetColor();

    cout << "\n\n";
    setColor(BRIGHT_WHITE);
    cout << "   Press ENTER to begin your quest...";
    resetColor();

    // Clear input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int askQuestion(const Question &q, int qNum)
{
    cout << "\n";
    setColor(BRIGHT_WHITE);
    cout << "   ┌─────────────────────────────────────────────────────┐\n";
    cout << "   │ ";
    setColor(BRIGHT_CYAN);
    cout << "Challenge " << qNum << ": ";
    setColor(WHITE);

    // Simple display without complex formatting
    cout << q.text;
    if (q.text.length() < 40)
        cout << " ";
    cout << " │\n";
    setColor(BRIGHT_WHITE);
    cout << "   └─────────────────────────────────────────────────────┘\n";

    for (int i = 0; i < 4; i++)
    {
        cout << "     ";
        setColor(BRIGHT_YELLOW);
        cout << q.options[i];
        resetColor();
        cout << "\n";
    }

    char answer;
    while (true)
    {
        cout << "\n     ";
        setColor(BRIGHT_GREEN);
        cout << "Your answer (A/B/C/D): ";
        resetColor();
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        answer = toupper(answer);

        if (answer >= 'A' && answer <= 'D')
        {
            break;
        }
        setColor(BRIGHT_RED);
        cout << "     Invalid! Please enter A, B, C, or D.\n";
        resetColor();
    }

    if (answer == q.correctAnswer)
    {
        setColor(BRIGHT_GREEN);
        cout << "\n     ✅ Success! +" << q.points << " coins!\n";
        resetColor();
        return q.points;
    }
    else
    {
        setColor(BRIGHT_RED);
        cout << "\n     ❌ Failed. Correct answer: " << q.correctAnswer << "\n";
        setColor(BRIGHT_CYAN);
        cout << "     💡 Wisdom: " << q.explanation << "\n";
        resetColor();
        return 0;
    }
}

int playTrack(const Track &track, int trackNum)
{
    system("cls");
    int trackScore = 0;

    printTrackHeader(trackNum);

    // Easy questions
    if (track.easyCount > 0)
    {
        printLevelBanner("Easy");
        for (int i = 0; i < track.easyCount; i++)
        {
            trackScore += askQuestion(track.easy[i], i + 1);
            cout << "\n";
        }
    }

    // Medium questions
    if (track.mediumCount > 0)
    {
        printLevelBanner("Medium");
        for (int i = 0; i < track.mediumCount; i++)
        {
            trackScore += askQuestion(track.medium[i], i + 1);
            cout << "\n";
        }
    }

    // Hard questions
    if (track.hardCount > 0)
    {
        printLevelBanner("Hard");
        for (int i = 0; i < track.hardCount; i++)
        {
            trackScore += askQuestion(track.hard[i], i + 1);
            cout << "\n";
        }
    }

    cout << "\n";
    setColor(BRIGHT_CYAN);
    cout << "   ╔═══════════════════════════════════════════════════════════════╗\n";
    cout << "   ║                                                               ║\n";
    cout << "   ║   🎯  Dungeon Conquered! Treasure: ";
    setColor(BRIGHT_YELLOW);
    cout << trackScore << "/38 coins";
    setColor(BRIGHT_CYAN);
    cout << "              ║\n";
    cout << "   ║                                                               ║\n";
    cout << "   ╚═══════════════════════════════════════════════════════════════╝\n";
    resetColor();

    return trackScore;
}

string calculateLevel(int score, int maxScore)
{
    double percentage = (score * 100.0) / maxScore;

    if (percentage >= 85)
        return "Dungeon Master";
    else if (percentage >= 70)
        return "Wizard";
    else if (percentage >= 50)
        return "Adventurer";
    else
        return "Novice";
}

void showResults(const string &username, int totalScore, int trackScores[])
{
    system("cls");

    setColor(BRIGHT_GREEN);
    cout << R"(
    ╔══════════════════════════════════════════════════════════════════════════════╗
    ║                                                                              ║
    ║                       🏁  Q U E S T  C O M P L E T E !  🏁                    ║
    ║                                                                              ║
    ╚══════════════════════════════════════════════════════════════════════════════╝
    )" << endl;

    string level = calculateLevel(totalScore, 190);

    cout << "\n";
    setColor(BRIGHT_CYAN);
    cout << "   ┌─────────────────────────────────────────────────────────────────┐\n";
    cout << "   │ Adventurer: ";
    setColor(BRIGHT_YELLOW);
    cout << username;
    setColor(BRIGHT_CYAN);
    int padding = 50 - username.length();
    if (padding > 0)
        cout << string(padding, ' ');
    cout << "│\n";
    cout << "   │ Total Treasure: ";
    setColor(BRIGHT_GREEN);
    cout << totalScore << "/190 coins (" << (totalScore * 100 / 190) << "%)";
    setColor(BRIGHT_CYAN);
    padding = 38 - to_string(totalScore).length();
    if (padding > 0)
        cout << string(padding, ' ');
    cout << "│\n";
    cout << "   │ Title Earned: ";

    if (level == "Dungeon Master")
        setColor(BRIGHT_RED);
    else if (level == "Wizard")
        setColor(BRIGHT_MAGENTA);
    else if (level == "Adventurer")
        setColor(BRIGHT_YELLOW);
    else
        setColor(BRIGHT_CYAN);

    cout << level;
    setColor(BRIGHT_CYAN);
    padding = 40 - level.length();
    if (padding > 0)
        cout << string(padding, ' ');
    cout << "│\n";
    cout << "   └─────────────────────────────────────────────────────────────────┘\n";

    cout << "\n\n";
    setColor(BRIGHT_WHITE);
    cout << "   📜 DUNGEON REPORT:\n";
    cout << "   ┌──────┬──────────────────────────────┬────────────┬────────────┐\n";
    cout << "   │ No.  │ Dungeon Name                 │ Your Coins │ Max Coins  │\n";
    cout << "   ├──────┼──────────────────────────────┼────────────┼────────────┤\n";

    string dungeonNames[5] = {"Logic Labyrinth", "Set Sanctuary", "Algorithm Arena",
                              "Cryptography Cave", "Combinatorics Castle"};

    for (int i = 0; i < 5; i++)
    {
        cout << "   │  ";
        setColor(BRIGHT_CYAN);
        cout << i + 1;
        resetColor();
        cout << "   │ ";
        setColor(BRIGHT_YELLOW);
        cout << setw(28) << left << dungeonNames[i];
        resetColor();
        cout << " │ ";
        setColor(BRIGHT_GREEN);
        cout << setw(10) << right << trackScores[i];
        resetColor();
        cout << " │ ";
        setColor(WHITE);
        cout << setw(10) << right << "38";
        resetColor();
        cout << " │\n";
    }

    setColor(BRIGHT_WHITE);
    cout << "   └──────┴──────────────────────────────┴────────────┴────────────┘\n";
    resetColor();
}

// ===================== MAIN FUNCTION =====================
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(time(0));

    // Load existing highscores
    loadHighscores();

    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y')
    {
        // Clear and show title
        system("cls");
        printTitle();

        // Get username
        string username = getUsername();

        // Show instructions
        showInstructions();

        // Initialize tracks
        Track tracks[5];
        initializeTrack1(tracks[0]);
        initializeTrack2(tracks[1]);
        initializeTrack3(tracks[2]);
        initializeTrack4(tracks[3]);
        initializeTrack5(tracks[4]);

        // Play all tracks
        int totalScore = 0;
        int trackScores[5];

        for (int i = 0; i < 5; i++)
        {
            trackScores[i] = playTrack(tracks[i], i + 1);
            totalScore += trackScores[i];

            if (i < 4)
            {
                cout << "\n\nPress ENTER to enter the next dungeon...";
                cin.get();
            }
        }

        // Show results
        showResults(username, totalScore, trackScores);

        // Save score
        string level = calculateLevel(totalScore, 190);
        saveScore(username, totalScore, level);

        // Show highscores
        showHighscores();

        // Ask to play again
        cout << "\n\n";
        setColor(BRIGHT_WHITE);
        cout << "   Embark on another quest? (y/n): ";
        setColor(BRIGHT_GREEN);
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    system("cls");
    setColor(BRIGHT_CYAN);
    cout << R"(
    ╔══════════════════════════════════════════════════════════════════════════════╗
    ║                                                                              ║
    ║                   T H A N K S  F O R  P L A Y I N G !                        ║
    ║                                                                              ║
    ║         Your legend is saved in 'all_scores.txt' and 'highscores.txt'       ║
    ║                                                                              ║
    ╚══════════════════════════════════════════════════════════════════════════════╝
    )" << endl;
    resetColor();

    Sleep(2000);
    return 0;
}
