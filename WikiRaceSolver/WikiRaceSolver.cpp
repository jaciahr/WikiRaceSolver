#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int readVertex(string name) {
	int vertex;
	string temp;
	ifstream iFile("SampleData/SampleVertices.txt");
	while (iFile) {
		iFile >> vertex;
		iFile >> name;
		if (temp == name) {
			return vertex;
		}
	}
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
	return edges;
}

int main() {
	cout << "Hello World!\n";
}
