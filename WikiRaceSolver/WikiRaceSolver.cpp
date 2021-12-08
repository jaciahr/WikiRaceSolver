#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Graph
{
private:
    int numVertices;
    bool** matrix;

public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        matrix = new bool* [numVertices];
        for (int i = 0; i < numVertices; i++) {
            matrix[i] = new bool[numVertices];
            for (int j = 0; j < numVertices; j++)
                matrix[i][j] = false;
        }
    }
    void insertEdge(int from, int to) {
        matrix[from][to] = true;
    }
    void removeEdge(int from, int to) {
        matrix[from][to] = false;
    }
    bool isEdge(int from, int to) {
        return matrix[from][to];
    }
    void printMatrix() {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }
};

int readVertexID(string name) {
    int vertex;
    string temp;
    ifstream iFile("SampleData/SampleVertices.txt");
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
    ifstream iFile("SampleData/SampleVertices.txt");
    while (iFile) {
        iFile >> vertex;
        getline(iFile, temp);
        if (vertex == ID)
            return temp.substr(2, temp.size() - 3);
    }
    iFile.close();
}

vector<int> readEdges(int vertex, Graph matrix) {
    int from;
    int to;
    vector<int> edges;
    ifstream iFile("SampleData/SampleEdges.txt");
    while (iFile) {
        iFile >> from;
        iFile >> to;
        if (from == vertex) {
            edges.push_back(to);
            matrix.insertEdge(from, to);
            /* NOTE: The above line should actually be above the if statement.
               The issue is that the ID's of the vertices are not equivalent
               to their line number. If you were to allocate a 2D array 
               to the ID of the last vertex (i.e., 4203055 x 4203055), it
               would be too large (at least for my PC's specs, since that's
               what the heap is dependent on). Should we rename vertex ID's
               to their appropriate line number? */
        }
    }
    iFile.close();
    return edges;
}

int main() {
    Graph exMatrix(41329);
    string exName = "Alexander Seton (d. 1332)";
    int exVertex = readVertexID(exName);
    vector<int> exEdges = readEdges(exVertex, exMatrix);
    cout << "This vertex: " << exName << " has these following edges: " << endl;
    for (int i = 0; i < exEdges.size(); i++) {
        cout << readVertexName(exEdges[i]) << endl;
    }
    //exMatrix.printMatrix();
}