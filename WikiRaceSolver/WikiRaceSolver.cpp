#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;

struct AdjacencyList {
    map<int, vector<int>> adjList;
    map<int, bool> visited;
    map<int, int> prevs;
    vector<int> results;

    void makeAdjList() {
        int from, to;
        ifstream iFile("SampleData/testedges.txt");
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
        if (!visited[target]) {
            results.push_back(-1);
            return;
        }
        while (target != start) {
            results.push_back(target);
            target = prevs[target];
        }
        results.push_back(start);
    }
};

struct elgGraph {
    vector<pair<int, int>> elg;
    vector<int> results;
    map<int, bool> visited;
    map<int, int> prevs;

    void MakeELG() {
        int from, to;
        ifstream iFile("SampleData/testedges.txt");
        while (iFile) {
            iFile >> from;
            iFile >> to;
            this->elg.push_back(make_pair(from, to));
        }
        iFile.close();
    }

    void BFS(int start, int target) {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        prevs[start] = -1;
        while (!q.empty()) {
            //vector<int> tempVector;
            int temp = q.front();
            q.pop();
            for (int i = 0; i < elg.size() - 1; i++) {
                if (temp == elg[i].first && !visited[elg[i].second]) {
                    visited[elg[i].second] = true;
                    prevs[elg[i].second] = temp;
                    q.push(elg[i].second);
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
            q.pop();
            for (int i = 0; i < elg.size() - 1; i++) {
                if (temp == elg[i].first && !visited[elg[i].second]) {
                    visited[elg[i].second] = true;
                    prevs[elg[i].second] = temp;
                    q.push(elg[i].second);
                }
            }
        }
        path(start, target);
    }

    void path(int start, int target) {
        if (!visited[target]) {
            results.push_back(-1);
            return;
        }
        while (target != start) {
            results.push_back(target);
            target = prevs[target];
        }
        results.push_back(start);
    }
};

int readVertexID(string name) {
    int vertex;
    string temp;
    ifstream iFile("SampleData/testvertices.txt");
    while (iFile) {
        iFile >> vertex;
        getline(iFile, temp);
        if (temp.substr(2, temp.size() - 3) == name) {
            iFile.close();
            return vertex;
        }
    }
    iFile.close();
    return -1;
}

string readVertexName(int ID) {
    int vertex;
    string temp;
    ifstream iFile("SampleData/testvertices.txt");
    while (iFile) {
        iFile >> vertex;
        getline(iFile, temp);
        if (vertex == ID) {
            iFile.close();
            return temp.substr(2, temp.size() - 3);
        }
    }
    iFile.close();
    return "";
}

int main() {
    AdjacencyList aGraph;
    elgGraph eGraph;

    int options, startID, targetID;
    string temp, start, target;
    cout << "Choose one of the options below:" << endl;
    cout << "1: Adjacency List Graph with BFS" << endl;
    cout << "2: Adjacency List Graph with DFS" << endl;
    cout << "3: Edge List Graph with BFS" << endl;
    cout << "4: Edge List Graph with DFS" << endl;
    getline(cin, temp);
    options = stoi(temp);
    cout << "Input name of starting site." << endl;
    getline(cin, start);
    cout << "Input name of target site." << endl;
    getline(cin, target);

    startID = readVertexID(start);
    targetID = readVertexID(target);

    if (options == 1) {
        aGraph.makeAdjList();
        aGraph.BFS(startID, targetID);
        cout << "There are " << aGraph.results.size() << " degrees of separation." << endl;
        cout << "The shortest path is: ";
        for (int i = 0; i < aGraph.results.size() - 1; i++) {
            cout << aGraph.results[i] << ", ";
        }
        cout << aGraph.results[aGraph.results.size() - 1] << "." << endl;
    }
    else if (options == 2) {
        aGraph.makeAdjList();
        aGraph.DFS(startID, targetID);
        cout << "There are " << aGraph.results.size() << " degrees of separation." << endl;
        cout << "The shortest path is: ";
        for (int i = 0; i < aGraph.results.size() - 1; i++) {
            cout << aGraph.results[i] << ", ";
        }
        cout << aGraph.results[aGraph.results.size() - 1] << "." << endl;
    }
    else if (options == 3) {
        eGraph.MakeELG();
        eGraph.BFS(startID, targetID);
        for (int i = 0; i < eGraph.results.size(); i++) {
            cout << eGraph.results[i] << endl;
        }

    }
    else if (options == 4) {
        eGraph.MakeELG();
        eGraph.DFS(startID, targetID);
        for (int i = 0; i < eGraph.results.size(); i++) {
            cout << eGraph.results[i] << endl;
        }
    }
}
