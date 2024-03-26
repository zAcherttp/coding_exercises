#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

bool HasInvalidCharacter(string &s)
{
    unordered_set<char> invalidChars = {'.', '/', '\\', '\'', '\"'};

    for (char ch : s)
    {
        if (invalidChars.count(ch))
        {
            return true;
        }
    }
    return false;
}

bool laKiTuDacBiet(char pw)
{
    unordered_set<char> specialChars = {'!', '@', '#', '$', '%', '^', '&', '*', '?', '_', '~'};
    return specialChars.count(pw);
}

string passwordStrength(string &pw)
{
    int score = 0;
    int BaseScore = 40;
    int Num_Excess = 0, Bonus_Excess = 3;
    int Num_Upper = 0, Bonus_Upper = 4;
    int Num_Numbers = 0, Bonus_Numbers = 5;
    int Num_Symbols = 0, Bonus_Symbols = 5;
    int Bonus_Combo = 0, Bonus_FlatLower = 0, Bonus_FlatNumber = 0;
    int length = pw.length();

    if (!HasInvalidCharacter(pw) && length > 7)
    {
        int numUpper = count_if(pw.begin(), pw.end(), ::isupper);
        int numNumbers = count_if(pw.begin(), pw.end(), ::isdigit);
        int numSymbols = count_if(pw.begin(), pw.end(), laKiTuDacBiet);
        bool hasLower = (length > 0) && (::islower(pw[0]));

        // Bonus_Combo
        int ComboScore = 0;
        if (numUpper > 0)
            ComboScore++;
        if (numSymbols > 0)
            ComboScore++;
        if (numNumbers > 0)
            ComboScore++;

        if (ComboScore == 1 || ComboScore == 2)
        {
            Bonus_Combo = 15;
        }
        else
        {
            Bonus_Combo = 25;
        }

        // Bonus_FlatLower
        if (Bonus_Combo == 0)
        {
            Bonus_FlatLower = -15;
        }

        // Bonus_FlatNumber
        int allNumber = 0;
        if (numNumbers > 0 && numSymbols + numUpper == 0 && !hasLower)
        {
            Bonus_FlatNumber = -35;
        }

        // Number_Execess
        Num_Excess = length - 8;

        // Number_Upper
        Num_Upper = numUpper;

        // Number_Numbers
        Num_Numbers = numNumbers;

        // Number_Symbols
        Num_Symbols = numSymbols;
    }
    else
    {
        return "KhongHopLe";
    }

    score = BaseScore + Num_Excess * Bonus_Excess + Num_Upper * Bonus_Upper + Num_Numbers * Bonus_Numbers + Num_Symbols * Bonus_Symbols + Bonus_Combo + Bonus_FlatLower + Bonus_FlatNumber;

    static const string grading[] = {"Yeu", "Vua", "Manh", "RatManh"};
    return grading[score >= 100 ? 3 : (score >= 75 ? 2 : (score >= 50 ? 1 : 0))];
}

int main()
{
    string password;
        getline(cin, password);
        cout << passwordStrength(password) << endl;
    return 0;
}
