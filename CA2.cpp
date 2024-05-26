#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

// Function to convert a word to its numeric value based on current assignment
int wordToNumber(const string& word, const unordered_map<char, int>& assignment) {
    int number = 0;
    for (char c : word) {
        number = number * 10 + assignment.at(c);
    }
    return number;
}

// Function to check if the current assignment satisfies the cryptarithmatic equation
bool isSolution(const string& word1, const string& word2, const string& result, const unordered_map<char, int>& assignment) {
    int num1 = wordToNumber(word1, assignment);
    int num2 = wordToNumber(word2, assignment);
    int numResult = wordToNumber(result, assignment);
    return num1 + num2 == numResult;
}

bool solveCryptarithm(vector<char>& uniqueChars, unordered_map<char, int>& assignment, vector<bool>& used, int index, const string& word1, const string& word2, const string& result) {
    if (index == uniqueChars.size()) {
        return isSolution(word1, word2, result, assignment);
    }

    for (int digit = 0; digit <= 9; ++digit) {
        if (!used[digit]) {
            // Ensure no leading zero
            if ((uniqueChars[index] == word1[0] || uniqueChars[index] == word2[0] || uniqueChars[index] == result[0]) && digit == 0) {
                continue;
            }
            used[digit] = true;
            assignment[uniqueChars[index]] = digit;

            if (solveCryptarithm(uniqueChars, assignment, used, index + 1, word1, word2, result)) {
                return true;
            }

            // Backtrack
            used[digit] = false;
            assignment[uniqueChars[index]] = -1;
        }
    }
    return false;
}

int main() {
    string word1, word2, result;
    cout << "Enter the first word: ";
    cin >> word1;
    cout << "Enter the second word: ";
    cin >> word2;
    cout << "Enter the result word: ";
    cin >> result;

    unordered_set<char> charSet;
    for (char c : word1 + word2 + result) {
        charSet.insert(c);
    }

    vector<char> uniqueChars(charSet.begin(), charSet.end());
    unordered_map<char, int> assignment;
    vector<bool> used(10, false);

    if (solveCryptarithm(uniqueChars, assignment, used, 0, word1, word2, result)) {
        cout << "Solution found:" << endl;
        for (const auto& pair : assignment) {
            cout << pair.first << " = " << pair.second << endl;
        }
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
