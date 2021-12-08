#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct AdjacencyList {
    unordered_map<int, vector<int>> adjList;

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
};

struct elgGraph {
    vector<pair<int, int>> elg;

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

};

int readVertexID(string name) {
    int vertex;
    string temp;
    ifstream iFile("SampleData/SampleNames.txt");
    while (iFile) {
        iFile >> vertex;
        getline(iFile, temp);
        if (temp.substr(2, temp.size() - 3) == name)
            return vertex;
    }
    iFile.close();
}

string readVertexName(int ID) {
    int vertex;
    string temp;
    ifstream iFile("SampleData/SampleNames.txt");
    while (iFile) {
        iFile >> vertex;
        getline(iFile, temp);
        if (vertex == ID)
            return temp.substr(2, temp.size() - 3);
    }
    iFile.close();
}

vector<int> readEdges(int vertex, AdjacencyList &adjList) {
    int from;
    int to;
    vector<int> edges;
    ifstream iFile("SampleData/SampleEdges.txt");
    while (iFile) {
        iFile >> from;
        iFile >> to;
        adjList.addEdge(from, to);
        if (from == vertex) {
            edges.push_back(to);
        }
    }
    iFile.close();
    return edges;
}

int main() {
    AdjacencyList exAdjList(100000);
    string exName = "Alexander Seton (d. 1332)";
    int exVertex = readVertexID(exName);
    vector<int> exEdges = readEdges(exVertex, exAdjList);
    cout << "This vertex: " << exName << " has these following edges: " << endl;
    for (int i = 0; i < exEdges.size(); i++) {
        cout << readVertexName(exEdges[i]) << endl;
    }
}
