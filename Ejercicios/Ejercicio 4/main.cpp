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
    unordered_map<int, vector<int>> adjList;

public:
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        if (adjList.find(v) == adjList.end()) {
            adjList[v] = {};
        }
    }

    const vector<int>& getNeighbors(int u) const {
        static const vector<int> empty;
        auto it = adjList.find(u);
        return (it != adjList.end()) ? it->second : empty;
    }
};

class GraphIterator {
public:
    virtual ~GraphIterator() = default;
    virtual bool hasNext() = 0;
    virtual int next() = 0;
};

class BFSIterator : public GraphIterator {
private:
    const Graph& graph;
    queue<int> q;
    unordered_set<int> visited;

public:
    BFSIterator(const Graph& g, int startNode) : graph(g) {
        q.push(startNode);
        visited.insert(startNode);
    }

    bool hasNext() override {
        return !q.empty();
    }

    int next() override {
        int current = q.front();
        q.pop();

        for (int neighbor : graph.getNeighbors(current)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }

        return current;
    }
};

class DFSIterator : public GraphIterator {
private:
    const Graph& graph;
    stack<int> s;
    unordered_set<int> visited;

public:
    DFSIterator(const Graph& g, int startNode) : graph(g) {
        s.push(startNode);
    }

    bool hasNext() override {
        while (!s.empty() && visited.find(s.top()) != visited.end()) {
            s.pop();
        }
        return !s.empty();
    }

    int next() override {
        int current = s.top();
        s.pop();
        visited.insert(current);

        const auto& neighbors = graph.getNeighbors(current);
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            if (visited.find(*it) == visited.end()) {
                s.push(*it);
            }
        }

        return current;
    }
};