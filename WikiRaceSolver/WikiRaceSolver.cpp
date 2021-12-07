#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int readVertex(string name) {
	string vertexString;
	int vertex;
	string temp;
	ifstream iFile("SampleData/SampleVertices.txt");
	string line;
	while (getline(iFile, line)) {
		vertexString = line.substr(0, 1);
		vertex = stoi(vertexString);
		temp = line.substr(3, line.length() - 4);
		if (temp == name)
			return vertex;
	}
	iFile.close();
}

vector<int> readEdges(int vertex) {
	int first;
	int second;
	vector<int> edges;
	ifstream iFile("SampleData/SampleEdges.txt");
	while (iFile) {
		iFile >> first;
		iFile >> second;
		if (first == vertex) {
			edges.push_back(second);
		}
		if (second == vertex) {
			edges.push_back(first);
		}
	}
	iFile.close();
	return edges;
}

int main() {
	string exName = "Alexander Seton (d. 1332)";
	int exVertex = readVertex(exName);
	vector<int> exEdges = readEdges(exVertex);
	cout << "This vertex: " << exName << " has " << exEdges.size() << " edges." << endl;
}
