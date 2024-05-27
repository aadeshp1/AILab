#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <utility>

using namespace std;

// State structure to hold the amount of water in both jugs
struct State {
    int jug1;
    int jug2;

    State(int x, int y) : jug1(x), jug2(y) {}

    bool operator<(const State &s) const {
        return tie(jug1, jug2) < tie(s.jug1, s.jug2);
    }
};

void printSolution(const vector<State> &solution) {
    for (const auto &state : solution) {
        cout << "(" << state.jug1 << ", " << state.jug2 << ")\n";
    }
}

bool dfs(int jug1Capacity, int jug2Capacity, int goal, vector<State> &solution, set<State> &visited, State current) {
    if (current.jug1 == goal || current.jug2 == goal) {
        solution.push_back(current);
        return true;
    }

    if (visited.count(current)) {
        return false;
    }

    visited.insert(current);

    vector<State> nextStates = {
        {jug1Capacity, current.jug2}, // Fill Jug 1
        {current.jug1, jug2Capacity}, // Fill Jug 2
        {0, current.jug2},            // Empty Jug 1
        {current.jug1, 0},            // Empty Jug 2
        {max(0, current.jug1 - (jug2Capacity - current.jug2)), min(jug2Capacity, current.jug1 + current.jug2)}, // Pour Jug 1 -> Jug 2
        {min(jug1Capacity, current.jug1 + current.jug2), max(0, current.jug2 - (jug1Capacity - current.jug1))}  // Pour Jug 2 -> Jug 1
    };

    for (const auto &next : nextStates) {
        if (dfs(jug1Capacity, jug2Capacity, goal, solution, visited, next)) {
            solution.push_back(current);
            return true;
        }
    }

    return false;
}

int main() {
    int jug1Capacity, jug2Capacity, goal;
    cout << "Enter capacity of Jug 1: ";
    cin >> jug1Capacity;
    cout << "Enter capacity of Jug 2: ";
    cin >> jug2Capacity;
    cout << "Enter the goal amount of water: ";
    cin >> goal;

    vector<State> solution;
    set<State> visited;

    State initialState(0, 0);

    if (dfs(jug1Capacity, jug2Capacity, goal, solution, visited, initialState)) {
        cout << "Solution found:\n";
        reverse(solution.begin(), solution.end());
        printSolution(solution);
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
