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
    void añadir(int u, int v) {
        adj[u].push_back(v);
        if (adj.find(v) == adj.end()) adj[v] = {};
    }

    const vector<int>& getVecinos(int u) const {
        static const vector<int> vacio;
        auto it = adj.find(u);
        return (it != adj.end()) ? it->second : vacio;
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
    unordered_set<int> visitado;

public:
    BFSIterator(const Graph& graph, int start) : g(graph) {
        q.push(start);
        visitado.insert(start);
    }

    bool hasNext() override {
        return !q.empty();
    }

    int next() override {
        int curr = q.front();
        q.pop();

        for (int neighbor : g.getVecinos(curr)) {
            if (visitado.find(neighbor) == visitado.end()) {
                visitado.insert(neighbor);
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
    unordered_set<int> visitado;

public:
    DFSIterator(const Graph& graph, int start) : g(graph) {
        s.push(start);
    }

    bool hasNext() override {
        while (!s.empty() && visitado.count(s.top())) {
            s.pop();
        }
        return !s.empty();
    }

    int next() override {
        int curr = s.top();
        s.pop();
        visitado.insert(curr);

        const auto& vecinos = g.getVecinos(curr);
        for (auto it = vecinos.rbegin(); it != vecinos.rend(); ++it) {
            if (!visitado.count(*it)) s.push(*it);
        }
        return curr;
    }
};