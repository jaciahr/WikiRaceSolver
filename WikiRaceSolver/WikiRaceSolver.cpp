#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int readVertex(string name) {
	int vertex;
	string temp;
	ifstream iFile("SampleData/SampleVertices.txt");
	while (iFile) {
		iFile >> vertex;
		iFile >> temp;
		if (temp == name) {
			return vertex;
		}
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
	cout << "Hello World!\n";
	string exName = "\"Alexander Seton(d. 1332)\"";
	int exVertex = readVertex(exName);
	vector<int> exEdges = readEdges(exVertex);
	cout << "This vertex: " << exName << " has " << exEdges.size() << " edges." << endl;
}
