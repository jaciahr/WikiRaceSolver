#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
#include <chrono>
using namespace std;

struct AdjacencyList {
    map<int, vector<int>> adjList;
    map<int, bool> visited;
    map<int, int> prevs;
    vector<int> results;

    void makeAdjList() {
        int from, to;
        ifstream iFile("SampleData/SampleEdges.txt");
        while (iFile) {
            iFile >> from;
            iFile >> to;
            adjList[from].push_back(to);
        }
        iFile.close();
    }

    void BFS(int start, int target) {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        prevs[start] = -1;
        while (!q.empty()) {
            int temp = q.front();
            if (temp == target)
                break;
            q.pop();
            for (int i : adjList[temp]) {
                if (!visited[i]) {
                    visited[i] = true;
                    prevs[i] = temp;
                    q.push(i);
                }
            }
        }
        path(start, target);
    }

    void DFS(int start, int target) {
        stack<int> q;
        q.push(start);
        visited[start] = true;
        prevs[start] = -1;
        while (!q.empty()) {
            int temp = q.top();
            if (temp == target)
                break;
            q.pop();
            for (int i : adjList[temp]) {
                if (!visited[i]) {
                    visited[i] = true;
                    prevs[i] = temp;
                    q.push(i);
                }
            }
        }
        path(start, target);
    }

    void path(int start, int target) {
        if (!visited[target])
            return;
        while (target != start) {
            results.push_back(target);
            target = prevs[target];
        }
        results.push_back(start);
    }
};

struct elgGraph {
    vector<pair<int, int>> elg;
    map<int, bool> visited;
    map<int, int> prevs;
    vector<int> results;

    void MakeELG() {
        int from, to;
        ifstream iFile("SampleData/SampleEdges.txt");
        while (iFile) {
            iFile >> from;
            iFile >> to;
            this->elg.push_back(make_pair(from, to));
        }
        iFile.close();
    }

    void BFS(int start, int target) {
        queue<int> q;
        q.push(target);
        visited[target] = true;
        prevs[target] = -1;
        while (!q.empty()) {
            bool quick = false;
            int temp = q.front();
            if (temp == start)
                break;
            q.pop();
            if (temp < 62975) {
                for (int i = 0; i < elg.size() - 1; i++) {
                    if (quick && temp != elg[i].second)
                        break;
                    if (temp == elg[i].second && !visited[elg[i].first]) {
                        visited[elg[i].first] = true;
                        prevs[elg[i].first] = temp;
                        q.push(elg[i].first);
                        quick = true;
                    }
                }
            }
            else {
                for (int i = elg.size() - 2; i > -1; i--) {
                    if (quick && temp != elg[i].second)
                        break;
                    if (temp == elg[i].second && !visited[elg[i].first]) {
                        visited[elg[i].first] = true;
                        prevs[elg[i].first] = temp;
                        q.push(elg[i].first);
                        quick = true;
                    }
                }
            }
        }
        path(target, start);
    }

    void DFS(int start, int target) {
        stack<int> q;
        q.push(target);
        visited[target] = true;
        prevs[target] = -1;
        while (!q.empty()) {
            bool quick = false;
            int temp = q.top();
            if (temp == start)
                break;
            q.pop();
            if (temp < 62975) {
                for (int i = 0; i < elg.size() - 1; i++) {
                    if (quick && temp != elg[i].second)
                        break;
                    if (temp == elg[i].second && !visited[elg[i].first]) {
                        visited[elg[i].first] = true;
                        prevs[elg[i].first] = temp;
                        q.push(elg[i].first);
                        quick = true;
                    }
                }
            }
            else {
                for (int i = elg.size() - 2; i > -1; i--) {
                    if (quick && temp != elg[i].second)
                        break;
                    if (temp == elg[i].second && !visited[elg[i].first]) {
                        visited[elg[i].first] = true;
                        prevs[elg[i].first] = temp;
                        q.push(elg[i].first);
                        quick = true;
                    }
                }
            }
        }
        path(target, start);
    }

    void path(int start, int target) {
        if (!visited[target])
            return;
        while (target != start) {
            results.push_back(target);
            target = prevs[target];
        }
        results.push_back(start);
    }
};

void readVertices(map<int, string>& key, map<string, int>& reversekey) {
    int vertex;
    string temp;
    ifstream iFile("SampleData/SampleNames.txt");
    while (iFile) {
        iFile >> vertex;
        getline(iFile, temp);
        temp = temp.substr(2, temp.size() - 3);
        key[vertex] = temp;
        reversekey[temp] = vertex;
    }
    iFile.close();
}

int main() {
    AdjacencyList aGraph;
    aGraph.makeAdjList();
    map<int, string> key;
    map<string, int> reversekey;
    elgGraph eGraph;
    eGraph.MakeELG();
    ofstream oFile("SampleData/ChronoResults.csv");

    for (int i = 0; i < 30; i += 1) {
        auto alpha = std::chrono::system_clock::now();
        aGraph.BFS(i, i + 1);
        auto omega = std::chrono::system_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(omega - alpha);
        cout << "There are " << aGraph.results.size() << " - 1 degrees of separation." << endl;
        cout << "Time for BFS in Adjacency List: " << time.count() << " nanoseconds. " << std::endl;
        oFile << time.count() << ", ";
        aGraph.visited.clear();
        aGraph.prevs.clear();
        aGraph.results.clear();

        alpha = std::chrono::system_clock::now();
        aGraph.DFS(i, i + 1);
        omega = std::chrono::system_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(omega - alpha);
        cout << "There are " << aGraph.results.size() << " - 1 degrees of separation." << endl;
        cout << "Time for BFS in Adjacency List: " << time.count() << " nanoseconds. " << std::endl;
        oFile << time.count() << ", ";
        aGraph.visited.clear();
        aGraph.prevs.clear();
        aGraph.results.clear();

        alpha = std::chrono::system_clock::now();
        eGraph.BFS(i, i + 1);
        omega = std::chrono::system_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(omega - alpha);
        cout << "There are " << eGraph.results.size() << " - 1 degrees of separation." << endl;
        cout << "Time for BFS in Adjacency List: " << time.count() << " nanoseconds. " << std::endl;
        oFile << time.count() << ", ";
        eGraph.visited.clear();
        eGraph.prevs.clear();
        eGraph.results.clear();

        alpha = std::chrono::system_clock::now();
        eGraph.DFS(i, i + 1);
        omega = std::chrono::system_clock::now();
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(omega - alpha);
        cout << "There are " << eGraph.results.size() << " - 1 degrees of separation." << endl;
        cout << "Time for BFS in Adjacency List: " << time.count() << " nanoseconds. " << std::endl;
        oFile << time.count() << endl;
        eGraph.visited.clear();
        eGraph.prevs.clear();
        eGraph.results.clear();
    }
    oFile.close();
}
