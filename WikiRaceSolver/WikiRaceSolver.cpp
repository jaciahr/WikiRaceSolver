#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>;
using namespace std;

struct AdjacencyList {
    unordered_map<int, vector<int>> adjList;
    unordered_map<int, bool> visited;
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
        int temp;
        queue<int> q;
        q.push(start);
        visited[start] = true;
        results.push_back(start);
        while (!q.empty()) {
            temp = q.front();
            results.push_back(temp);
            q.pop();
            for (int i = 0; i < adjList[temp].size(); i++) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    void DFS(int start, int target) {
        results.push_back(start);
        if (start == target) {
            results.push_back(target);
            return;
        }
        for (int i = 0; i < adjList[start].size(); i++) {
            if (!visited[i]) {
                visited[i] = true;
                DFS(i, target);
            }
        }
    }
};

struct elgGraph {
    vector<pair<int, int>> elg;
    vector<int> result;

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

    }

    void DFS(int start, int target) {

    }
};

int readVertexID(string name) {
    int vertex;
    string temp;
    ifstream iFile("SampleData/SampleNames.txt");
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
    ifstream iFile("SampleData/SampleNames.txt");
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

//this code will prbably be taken out, but let's keep it for now as a reference
//vector<int> readEdges(int vertex) {
//    int from, to;
//    vector<int> edges;
//    ifstream iFile("SampleData/SampleEdges.txt");
//    while (iFile) {
//        iFile >> from;
//        iFile >> to;
//        if (from == vertex) {
//            edges.push_back(to);
//        }
//    }
//    iFile.close();
//    return edges;
//}

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
        for (int i = 0; i < aGraph.results.size(); i++) {
            cout << aGraph.results[i] << endl;
        }
    } else if (options == 2) {
        aGraph.makeAdjList();
        aGraph.DFS(startID, targetID);
        for (int i = 0; i < aGraph.results.size(); i++) {
            cout << aGraph.results[i] << endl;
        }
    } else if (options == 3) {
        eGraph.MakeELG();
        eGraph.BFS(startID, targetID);

    } else if (options == 4) {
        eGraph.MakeELG();
        eGraph.DFS(startID, targetID);
    }

    //this code will prbably be taken out, but let's keep it for now as a reference
    /*string exName = "Alexander Seton (d. 1332)";
    int exVertex = readVertexID(exName);
    vector<int> exEdges = readEdges(exVertex);
    cout << "This vertex: " << exName << " has these following edges: " << endl;
    for (int i = 0; i < exEdges.size(); i++) {
        cout << readVertexName(exEdges[i]) << endl;
    }*/
}
