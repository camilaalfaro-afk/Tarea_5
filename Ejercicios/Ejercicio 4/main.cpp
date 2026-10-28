#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <memory>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adj;

public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (adj.find(v) == adj.end()) adj[v] = {};
    }

    const vector<int>& getNeighbors(int u) const {
        static const vector<int> empty;
        auto it = adj.find(u);
        return (it != adj.end()) ? it->second : empty;
    }
};

// iterador interfaz
class GraphIterator {
public:
    virtual ~GraphIterator() = default;
    virtual bool hasNext() = 0;
    virtual int next() = 0;
};

// Iterador BFS
class BFSIterator : public GraphIterator {
private:
    const Graph& g;
    queue<int> q;
    unordered_set<int> visited;

public:
    BFSIterator(const Graph& graph, int start) : g(graph) {
        q.push(start);
        visited.insert(start);
    }

    bool hasNext() override {
        return !q.empty();
    }

    int next() override {
        int curr = q.front();
        q.pop();

        for (int neighbor : g.getNeighbors(curr)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
        return curr;
    }
};

// iterador dfs
class DFSIterator : public GraphIterator {
private:
    const Graph& g;
    stack<int> s;
    unordered_set<int> visited;

public:
    DFSIterator(const Graph& graph, int start) : g(graph) {
        s.push(start);
    }

    bool hasNext() override {
        while (!s.empty() && visited.count(s.top())) {
            s.pop();
        }
        return !s.empty();
    }

    int next() override {
        int curr = s.top();
        s.pop();
        visited.insert(curr);

        const auto& neighbors = g.getNeighbors(curr);
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            if (!visited.count(*it)) s.push(*it);
        }
        return curr;
    }
};