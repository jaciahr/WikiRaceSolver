#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;

struct AdjacencyList {
    unordered_map<int, vector<int>> adjList;
    unordered_map<int, bool> visited;
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
        while (!q.empty()) {
            vector<int> tempVector;
            int temp = q.front();
            results.push_back(temp);
            q.pop();
            for (int i : adjList[temp]) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
            for (int i = 0; i < tempVector.size(); i++) {
                q.push(tempVector[i]);
            }
        }
    }

    void DFS(int start, int target) {
        stack<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            vector<int> tempVector;
            int temp = q.top();
            results.push_back(temp);
            q.pop();
            for (int i : adjList[temp]) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
            sort(tempVector.begin(), tempVector.begin() + tempVector.size());
            for (int i = 0; i < tempVector.size(); i++) {
                q.push(tempVector[i]);
            }
        }
    }
};

struct elgGraph {
    vector<pair<int, int>> elg;
    vector<int> results;
    unordered_map<int, bool> visited;

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
        while (!q.empty()) {
            //vector<int> tempVector;
            int temp = q.front();
            results.push_back(temp);
            q.pop();
            if (!visited[elg[temp].second]) {
                for (auto i : elg) {
                    if (temp == i.first) {
                        q.push(i.second);
                    }
                }
                visited[elg[temp].second] = true;
            }
            /*for (int i = 0; i < tempVector.size(); i++) {
                q.push(tempVector[i]);
            }*/
        }
    }

    void DFS(int start, int target) {
        /*results.push_back(start);
        if (start == target) {
            results.push_back(target);
            return;
        }
        for (int i = 0; i < elg[start].size(); i++) {
            if (!visited[i]) {
                visited[i] = true;
                DFS(i, target);
            }
        }*/
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
    }
}
