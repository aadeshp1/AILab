#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;
void printPuzzle(const vector<vector<int>>& puzzle);


struct State {
    vector<vector<int>> puzzle;
    int heuristic;
    string hash; 

    State(vector<vector<int>> p, int h) : puzzle(p), heuristic(h) {
        hash = convertToString(puzzle);
    }

    bool operator<(const State& other) const {
        return heuristic > other.heuristic; 
    }

    string convertToString(const vector<vector<int>>& state) {
        string str;
        for (const auto& row : state) {
            for (int value : row) {
                str += to_string(value) + ",";
            }
        }
        return str;
    }
};


int manhattanDistance(const vector<vector<int>>& state, const vector<vector<int>>& goalState) {
    int distance = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int value = state[i][j];
            if (value != 0) {
                for (int k = 0; k < 3; ++k) {
                    for (int l = 0; l < 3; ++l) {
                        if (value == goalState[k][l]) {
                            distance += abs(k - i) + abs(l - j);
                        }
                    }
                }
            }
        }
    }
    return distance;
}


bool isGoalState(const vector<vector<int>>& state, const vector<vector<int>>& goalState) {
    return state == goalState;
}


vector<vector<vector<int>>> generateMoves(const vector<vector<int>>& state) {
    vector<vector<vector<int>>> moves;
    int dx[] = {-1, 1, 0, 0}; 
    int dy[] = {0, 0, -1, 1};
    int x, y;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] == 0) {
                x = i;
                y = j;
                break;
            }
        }
    }
    for (int k = 0; k < 4; ++k) {
        int newX = x + dx[k];
        int newY = y + dy[k];
        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
            vector<vector<int>> newState = state;
            swap(newState[x][y], newState[newX][newY]);
            moves.push_back(newState);
        }
    }
    return moves;
}


vector<vector<int>> solvePuzzle(vector<vector<int>>& initialState, const vector<vector<int>>& goalState, vector<State>& steps) {
    priority_queue<State> frontier;
    unordered_set<string> explored;
    int stepCounter = 0;

    int initialHeuristic = manhattanDistance(initialState, goalState);
    State initial(initialState, initialHeuristic);
    frontier.push(initial);

    while (!frontier.empty()) {
        State current = frontier.top();
        frontier.pop();

        steps.push_back(current); 
        ++stepCounter;

        if (isGoalState(current.puzzle, goalState)) {
            return current.puzzle;
        }

        explored.insert(current.hash);

        vector<vector<vector<int>>> nextMoves = generateMoves(current.puzzle);
        for (const auto& nextState : nextMoves) {
            string nextStateString = current.convertToString(nextState); 
            if (explored.find(nextStateString) == explored.end()) {
                int heuristic = manhattanDistance(nextState, goalState);
                State nextStateNode(nextState, heuristic);
                frontier.push(nextStateNode);
            }
        }
    }

    return {}; 
}


void printPuzzle(const vector<vector<int>>& puzzle) {
    for (const auto& row : puzzle) {
        for (int value : row) {
            if (value == 0) {
                cout << "  "; 
            } else {
                cout << value << " ";
            }
        }
        cout << endl;
    }
}


vector<vector<int>> inputPuzzle(const string& prompt) {
    vector<vector<int>> puzzle(3, vector<int>(3));
    cout << prompt << " (use 0 for empty tile):\n";
    for (int i = 0; i < 3; ++i) {
        cout << "Row " << (i + 1) << ": ";
        for (int j = 0; j < 3; ++j) {
            cin >> puzzle[i][j];
        }
    }
    return puzzle;
}


int main() {
    vector<vector<int>> initialState = inputPuzzle("Enter the initial puzzle configuration");
    vector<vector<int>> goalState = inputPuzzle("Enter the goal puzzle configuration");

    

    vector<State> steps; 

    vector<vector<int>> solution = solvePuzzle(initialState, goalState, steps);

    if (!solution.empty()) {
        cout << "\nSolution:" << endl;
        cout<<endl;
        for (size_t i = 0; i < steps.size(); ++i) {
            cout << "Step " << i+1 << ":" << endl;
            printPuzzle(steps[i].puzzle); 
            cout << endl;
        }
        cout << "Total steps: " << steps.size() << endl;
    } else {
        cout << "\nNo solution found." << endl;
    }

    return 0;
}
