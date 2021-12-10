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

void readVertices(map<int, string> &key, map<string, int> &reversekey) {
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
    elgGraph eGraph;
    map<int, string> key;
    map<string, int> reversekey;
    bool aGraphCheck = false, eGraphCheck = false, keyCheck = false;
    string options = "";

    while (options != "5") {
        string start, target;
        int startID, targetID;
        cout << "Choose one of the options below:" << endl;
        cout << "1: Adjacency List Graph with BFS" << endl;
        cout << "2: Adjacency List Graph with DFS" << endl;
        cout << "3: Edge List Graph with BFS" << endl;
        cout << "4: Edge List Graph with DFS" << endl;
        cout << "5: Exit" << endl;
        getline(cin, options);
        if (options != "1" && options != "2" && options != "3" && options != "4") {
            if (options == "5")
                return 0;
            cout << "Invalid option choice." << endl;
            continue;
        }
        if (!keyCheck) {
            keyCheck = true;
            readVertices(key, reversekey);
        }
        cout << "Input name of starting site." << endl;
        getline(cin, start);
        if (!reversekey.count(start)) {
            cout << "That site does not exist within the database." << endl;
            continue;
        }
        startID = reversekey[start];
        cout << "Input name of target site." << endl;
        getline(cin, target);
        if (!reversekey.count(target)) {
            cout << "That site does not exist within the database." << endl;
            continue;
        }
        targetID = reversekey[target];

        if (options == "1") {
            if (!aGraphCheck) {
                aGraphCheck = true;
                aGraph.makeAdjList();
            }
            aGraph.BFS(startID, targetID);
            if (aGraph.results.size() == 0) {
                cout << "There is no path between these sites." << endl;
                continue;
            }
            cout << "There are " << aGraph.results.size() - 1 << " degrees of separation." << endl;
            cout << "The shortest path is: ";
            for (int i = aGraph.results.size() - 1; i > 0; i--)
                cout << key[aGraph.results[i]] << ", ";
            cout << key[aGraph.results[0]] << "." << endl;
        }
        else if (options == "2") {
            if (!aGraphCheck) {
                aGraphCheck = true;
                aGraph.makeAdjList();
            }
            aGraph.DFS(startID, targetID);
            if (aGraph.results.size() == 0) {
                cout << "There is no path between these sites." << endl;
                continue;
            }
            cout << "There are " << aGraph.results.size() - 1 << " degrees of separation." << endl;
            cout << "The shortest path is: ";
            for (int i = aGraph.results.size() - 1; i > 0; i--)
                cout << key[aGraph.results[i]] << ", ";
            cout << key[aGraph.results[0]] << "." << endl;
        }
        else if (options == "3") {
            if (!eGraphCheck) {
                eGraphCheck = true;
                eGraph.MakeELG();
            }
            eGraph.BFS(startID, targetID);
            if (eGraph.results.size() == 0) {
                cout << "There is no path between these sites." << endl;
                continue;
            }
            cout << "There are " << eGraph.results.size() - 1 << " degrees of separation." << endl;
            cout << "The shortest path is: ";
            for (int i = 0; i < eGraph.results.size() - 1; i++)
                cout << key[eGraph.results[i]] << ", ";
            cout << key[eGraph.results[eGraph.results.size() - 1]] << "." << endl;
        }
        else if (options == "4") {
            if (!eGraphCheck) {
                eGraphCheck = true;
                eGraph.MakeELG();
            }
            eGraph.DFS(startID, targetID);
            if (eGraph.results.size() == 0) {
                cout << "There is no path between these sites." << endl;
                continue;
            }
            cout << "There are " << eGraph.results.size() - 1 << " degrees of separation." << endl;
            cout << "The shortest path is: ";
            for (int i = 0; i < eGraph.results.size() - 1; i++)
                cout << key[eGraph.results[i]] << ", ";
            cout << key[eGraph.results[eGraph.results.size() - 1]] << "." << endl;
        }
        aGraph.visited.clear();
        aGraph.prevs.clear();
        aGraph.results.clear();
        eGraph.visited.clear();
        eGraph.prevs.clear();
        eGraph.results.clear();
    }
}
