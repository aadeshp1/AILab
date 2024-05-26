#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <list>

using namespace std;

struct Edge {
    string source, dest;
    int weight;

    Edge(string source, string dest, int weight) : source(source), dest(dest), weight(weight) {}
};

struct PQNode {
    string node;
    int priority;
    int distance;

    PQNode(string node, int priority, int distance) : node(node), priority(priority), distance(distance) {}

    bool operator<(const PQNode& other) const {
        return priority > other.priority;
    }
};

class Graph {
public:
    unordered_map<string, vector<Edge>> adjList;

    Graph(const vector<Edge>& edges) {
        for (const auto& edge : edges) {
            adjList[edge.source].push_back(edge);
        }
    }
};

map<string, int> heuristic = {
    {"Arad", 366}, {"Bucharest", 0}, {"Craiova", 160}, {"Dobreta", 242},
    {"Eforie", 161}, {"Fagaras", 176}, {"Giurgiu", 77}, {"Hirsova", 151},
    {"Iasi", 226}, {"Lugoj", 244}, {"Mehadia", 241}, {"Neamt", 234},
    {"Oradea", 380}, {"Pitesti", 100}, {"Rimnicu Vilcea", 193}, {"Sibiu", 253},
    {"Timisoara", 329}, {"Urziceni", 80}, {"Vaslui", 199}, {"Zerind", 374}
};

void bestFirstSearch(Graph& graph, const string& src, const string& dest) {
    priority_queue<PQNode> pq;
    unordered_set<string> visited;
    unordered_map<string, string> path;

    pq.push(PQNode(src, 0, 0));

    while (!pq.empty()) {
        PQNode currentNode = pq.top();
        pq.pop();

        string node = currentNode.node;
        int currentPriority = currentNode.priority;
        int currentDistance = currentNode.distance;

        visited.insert(node);

        if (node == dest) {
            cout << "Path: ";
            list<string> reversePath;
            while (node != src) {
                reversePath.push_front(node);
                node = path[node];
            }
            reversePath.push_front(src);
            for (const auto& city : reversePath) {
                cout << city << " -> ";
            }
            cout << "\nTotal Distance: " << currentDistance << " km\n";
            break;
        }

        for (const auto& edge : graph.adjList[node]) {
            if (!visited.count(edge.dest)) {
                int priority = edge.weight + heuristic[edge.dest];
                int newDistance = currentDistance + edge.weight;
                pq.push(PQNode(edge.dest, priority, newDistance));
                path[edge.dest] = node;
            }
        }
    }
}

int main() {
    vector<Edge> edges = {
        Edge("Arad", "Zerind", 75), Edge("Arad", "Sibiu", 140), Edge("Arad", "Timisoara", 118),
        Edge("Zerind", "Oradea", 71), Edge("Oradea", "Sibiu", 151), Edge("Timisoara", "Lugoj", 111),
        Edge("Lugoj", "Mehadia", 70), Edge("Mehadia", "Dobreta", 75), Edge("Dobreta", "Craiova", 120),
        Edge("Craiova", "Rimnicu Vilcea", 146), Edge("Craiova", "Pitesti", 138),
        Edge("Rimnicu Vilcea", "Sibiu", 80), Edge("Rimnicu Vilcea", "Pitesti", 97),
        Edge("Sibiu", "Fagaras", 99), Edge("Fagaras", "Bucharest", 211),
        Edge("Pitesti", "Bucharest", 101), Edge("Bucharest", "Giurgiu", 90),
        Edge("Bucharest", "Urziceni", 85), Edge("Urziceni", "Vaslui", 142),
        Edge("Vaslui", "Iasi", 92), Edge("Iasi", "Neamt", 87), Edge("Urziceni", "Hirsova", 98),
        Edge("Hirsova", "Eforie", 86)
    };

    Graph graph(edges);

    string src = "Arad";
    string dest = "Bucharest";

    bestFirstSearch(graph, src, dest);

    return 0;
}
