#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
public:
    vector<vector<char>> data; 
    int level; 
    int fval; 

    Node(vector<vector<char>> data, int level, int fval) {
        this->data = data;
        this->level = level;
        this->fval = fval;
    }

    vector<Node> generate_child(); 
    vector<vector<char>> shuffle(vector<vector<char>> puz, int x1, int y1, int x2, int y2); 
    vector<vector<char>> copy(vector<vector<char>> root); 
    pair<int, int> find(vector<vector<char>> puz, char x); 
};


vector<Node> Node::generate_child() {
    vector<Node> children;
    auto blank_pos = find(data, '_');
    int x = blank_pos.first;
    int y = blank_pos.second;
    vector<pair<int, int>> val_list = {{x, y - 1}, {x, y + 1}, {x - 1, y}, {x + 1, y}};
    for (auto i : val_list) {
        auto child_data = shuffle(data, x, y, i.first, i.second);
        if (!child_data.empty()) {
            Node child_node(child_data, level + 1, 0);
            children.push_back(child_node);
        }
    }
    return children;
}


vector<vector<char>> Node::shuffle(vector<vector<char>> puz, int x1, int y1, int x2, int y2) {
    if (x2 >= 0 && x2 < puz.size() && y2 >= 0 && y2 < puz.size()) {
        vector<vector<char>> temp_puz = puz;
        char temp = temp_puz[x2][y2];
        temp_puz[x2][y2] = temp_puz[x1][y1];
        temp_puz[x1][y1] = temp;
        return temp_puz;
    } else {
        return {};
    }
}


vector<vector<char>> Node::copy(vector<vector<char>> root) {
    vector<vector<char>> temp;
    for (auto i : root) {
        temp.push_back(i);
    }
    return temp;
}


pair<int, int> Node::find(vector<vector<char>> puz, char x) {
    for (size_t i = 0; i < puz.size(); ++i) {
        for (size_t j = 0; j < puz[i].size(); ++j) {
            if (puz[i][j] == x) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}


class Puzzle {
public:
    int n; 
    vector<Node> open; 
    vector<Node> closed; 

    Puzzle(int size) {
        n = size;
        open = vector<Node>();
        closed = vector<Node>();
    }

    vector<vector<char>> accept(); 
    int f(Node start, vector<vector<char>> goal); 
    int h(vector<vector<char>> start, vector<vector<char>> goal); 
    void process(); 
};


vector<vector<char>> Puzzle::accept() {
    vector<vector<char>> puz;
    for (int i = 0; i < n; ++i) {
        vector<char> temp;
        string input;
        getline(cin, input);
        for (char c : input) {
            if (c != ' ') {
                temp.push_back(c);
            }
        }
        puz.push_back(temp);
    }
    return puz;
}


int Puzzle::f(Node start, vector<vector<char>> goal) {
    return h(start.data, goal) + start.level;
}


int Puzzle::h(vector<vector<char>> start, vector<vector<char>> goal) {
    int temp = 0;
    for (size_t i = 0; i < start.size(); ++i) {
        for (size_t j = 0; j < start[i].size(); ++j) {
            if (start[i][j] != goal[i][j] && start[i][j] != '_') {
                temp += 1;
            }
        }
    }
    return temp;
}


void Puzzle::process() {
    cout << "Enter the start state matrix \n";
    vector<vector<char>> start = accept();
    cout << "Enter the goal state matrix \n";
    vector<vector<char>> goal = accept();

    Node start_node(start, 0, 0);
    start_node.fval = f(start_node, goal);
    open.push_back(start_node);
    cout << "\n\n";
    while (true) {
        Node cur = open[0];
        cout << "\n";
        cout << "  | \n";
        cout << "  | \n";
        cout << " \\'/ \n";
        for (auto i : cur.data) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << "\n";
        }
        if (h(cur.data, goal) == 0) {
            break;
        }
        for (auto i : cur.generate_child()) {
            i.fval = f(i, goal);
            open.push_back(i);
        }
        closed.push_back(cur);
        open.erase(open.begin());

        sort(open.begin(), open.end(), [](Node const& a, Node const& b) {
            return a.fval < b.fval;
        });
    }
}

int main() {
    Puzzle puz(3); 
    puz.process(); 
    return 0;
}

