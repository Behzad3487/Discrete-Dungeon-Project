#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

/* =======================
   COLOR UTILITY
   ======================= */
void setColor(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/* =======================
   TYPING EFFECT
   ======================= */
void typePrint(const string& text, int delay = 8)
{
    for (char c : text)
    {
        cout << c;
        Sleep(delay);
    }
    cout << endl;
}

/* =======================
   ASCII GAME HEADER
   ======================= */
void showHeader()
{
    system("cls");
    setColor(14);
    cout << R"(

 ██████╗ ██╗███████╗ ██████╗██████╗ ███████╗████████╗███████╗
 ██╔══██╗██║██╔════╝██╔════╝██╔══██╗██╔════╝╚══██╔══╝██╔════╝
 ██║  ██║██║███████╗██║     ██████╔╝█████╗     ██║   █████╗
 ██║  ██║██║╚════██║██║     ██╔══██╗██╔══╝     ██║   ██╔══╝
 ██████╔╝██║███████║╚██████╗██║  ██║███████╗   ██║   ███████╗
 ╚═════╝ ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝

 ██████╗ ██╗   ██╗███╗   ██╗ ██████╗ ███████╗ ██████╗ ███╗   ██╗
 ██╔══██╗██║   ██║████╗  ██║██╔════╝ ██╔════╝██╔═══██╗████╗  ██║
 ██║  ██║██║   ██║██╔██╗ ██║██║  ███╗█████╗  ██║   ██║██╔██╗ ██║
 ██║  ██║██║   ██║██║╚██╗██║██║   ██║██╔══╝  ██║   ██║██║╚██╗██║
 ██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████╗╚██████╔╝██║ ╚████║
 ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝

            === SYLLABUS QUEST : FINAL EDITION ===
)";
    setColor(7);
}

/* =======================
   QUESTION STRUCT
   ======================= */
struct Question
{
    string text;
    vector<string> options;
    int correctMCQ;
    int correctNum;
    bool isMCQ;
};

/* =======================
   TRACK CLASS
   ======================= */
class Track
{
public:
    string name;
    vector<Question> qs;
    bool cleared = false;

    Track(string n) : name(n) {}

    void addMCQ(string t, vector<string> o, int c)
    {
        qs.push_back({t, o, c, -1, true});
    }

    void addNUM(string t, int c)
    {
        qs.push_back({t, {}, -1, c, false});
    }

    bool play(int& score)
    {
        int correct = 0;
        setColor(11);
        typePrint("\nEntering Track: " + name + "\n");
        setColor(7);

        for (size_t i = 0; i < qs.size(); i++)
        {
            cout << "\nQ" << i + 1 << ": " << qs[i].text << endl;

            if (qs[i].isMCQ)
            {
                for (size_t j = 0; j < qs[i].options.size(); j++)
                    cout << j + 1 << ") " << qs[i].options[j] << endl;

                int ans;
                cout << "Answer: ";
                cin >> ans;

                if (ans == qs[i].correctMCQ)
                {
                    setColor(10);
                    typePrint("✔ Correct");
                    setColor(7);
                    correct++;
                    score += 10;
                }
                else
                {
                    setColor(12);
                    typePrint("✘ Wrong");
                    setColor(7);
                }
            }
            else
            {
                int ans;
                cout << "Numeric Answer: ";
                cin >> ans;

                if (ans == qs[i].correctNum)
                {
                    setColor(10);
                    typePrint("✔ Correct");
                    setColor(7);
                    correct++;
                    score += 15;
                }
                else
                {
                    setColor(12);
                    typePrint("✘ Wrong");
                    setColor(7);
                }
            }
        }

        cleared = (correct >= 2);
        return cleared;
    }
};

/* =======================
   MENU DISPLAY
   ======================= */
void showMenu(const vector<Track>& t, int lives, int score)
{
    setColor(14);
    cout << "\n========== TRACK SELECTION ==========\n";
    setColor(7);

    for (size_t i = 0; i < t.size(); i++)
    {
        cout << i + 1 << ") " << t[i].name << " ";

        if (i == 0 || t[i - 1].cleared)
        {
            if (t[i].cleared)
            {
                setColor(11);
                cout << "[CLEARED]";
            }
            else
            {
                setColor(10);
                cout << "[OPEN]";
            }
        }
        else
        {
            setColor(12);
            cout << "[LOCKED]";
        }
        setColor(7);
        cout << endl;
    }

    cout << "\nLives: ";
    setColor(12); cout << lives;
    setColor(7);
    cout << "   Score: ";
    setColor(14); cout << score;
    setColor(7);

    cout << "\nChoose track (0 to quit): ";
}

/* =======================
   MAIN
   ======================= */
int main()
{
    SetConsoleOutputCP(CP_UTF8); 
    SetConsoleCP(CP_UTF8);
    int lives = 3, score = 0;
    showHeader();

    typePrint("Welcome, Scholar. This dungeon tests your Discrete Mathematics mastery.\n");

    Track logic("Logic & Arguments");
    logic.addMCQ("What makes an argument valid?",
        {"True conclusion", "Conclusion follows from premises", "True premises", "All false"},
        2);
    logic.addMCQ("Contrapositive of P → Q?",
        {"Q → P", "¬P → ¬Q", "¬Q → ¬P", "P → ¬Q"},
        3);
    logic.addNUM("Truth table rows for 2 propositions:", 4);

    Track sets("Sets & Venn Diagrams");
    sets.addNUM("Power set size of 4 elements:", 16);
    sets.addMCQ("A ∩ B represents:",
        {"Only A", "Only B", "Common region", "Outside"},
        3);
    sets.addNUM("|A|=10, |B|=6, |A∩B|=2, find |A∪B|:", 14);

    Track algo("Algorithms");
    algo.addMCQ("Binary search time complexity:",
        {"O(n)", "O(log n)", "O(n log n)", "O(1)"},
        2);
    algo.addNUM("Max comparisons for binary search (32 items):", 5);
    algo.addMCQ("Binary search requires:",
        {"Graph", "Sorted array", "Stack", "Queue"},
        2);

    Track crypto("Number Theory & Cryptography");
    crypto.addNUM("Compute 37 mod 8:", 5);
    crypto.addMCQ("Caesar cipher shift 3: A becomes?",
        {"C", "D", "E", "B"},
        2);
    crypto.addNUM("Decrypt value 12 with shift 3:", 9);

    Track count("Counting & Combinatorics");
    count.addMCQ("Sequential independent choices use:",
        {"Sum rule", "Product rule", "Division rule", "Subtraction rule"},
        2);
    count.addNUM("Number of ways to choose 3 from 5:", 10);
    count.addNUM("Minimum people to ensure same birth month:", 13);

    vector<Track> tracks = {logic, sets, algo, crypto, count};

    while (lives > 0)
    {
        showMenu(tracks, lives, score);
        int ch;
        cin >> ch;

        if (ch == 0) break;
        if (ch < 1 || ch > 5) continue;

        int i = ch - 1;

        if (i != 0 && !tracks[i - 1].cleared)
        {
            setColor(12);
            typePrint("Track is LOCKED.");
            setColor(7);
            continue;
        }

        if (tracks[i].cleared)
        {
            setColor(11);
            typePrint("Already CLEARED.");
            setColor(7);
            continue;
        }

        bool win = tracks[i].play(score);
        if (!win)
        {
            lives--;
            setColor(12);
            typePrint("Track failed. Life lost.");
            setColor(7);
        }
        else
        {
            setColor(10);
            typePrint("Track CLEARED!");
            setColor(7);
        }
    }

    setColor(14);
    typePrint("\n=== GAME OVER ===");
    setColor(7);
    cout << "Final Score: " << score << endl;
    cout << "Thanks for playing.\n";

    return 0;
}
