#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct node	{
	string name;
	int weight;
	vector<node*> children;
};

int main(int argc, char *argv[])
{
	int numValid = 0;
	vector<int> totals;

	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	ifstream infile(argv[1]);
	string line;

	vector <node> nodesToBeLinked;

	while (getline(infile, line))	{
		stringstream stream(line);
		string name, weight;
		int weightInt;
		stream >> name >> weight;
		vector<string> children;

		while(stream)	{
			string child;
			stream >> child;
			children.push_back(child);
		}

		node tmp {name, stoi(weight.substr(1, weight.size() - 2)), null};

	}

	cout << "Total number of valid passphrases = " << numValid << endl;

	return 0;
}
