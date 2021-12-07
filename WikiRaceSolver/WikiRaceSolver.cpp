#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

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

vector<int> readEdges(int vertex) {
	int from;
	int to;
	vector<int> edges;
	ifstream iFile("SampleData/SampleEdges.txt");
	while (iFile) {
		iFile >> from;
		iFile >> to;
		if (from == vertex) {
			edges.push_back(to);
		}
	}
	iFile.close();
	return edges;
}

int main() {
	string exName = "Alexander Seton (d. 1332)";
	int exVertex = readVertexID(exName);
	vector<int> exEdges = readEdges(exVertex);
	cout << "This vertex: " << exName << " has these following edges: " << endl;
	for (int i = 0; i < exEdges.size(); i++) {
		cout << readVertexName(exEdges[i]) << endl;
	}
}
