#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> split(const string& s, char delimiter)	{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
		tokens.push_back(token);
	return tokens;
}

int main()
{

	string path;
	cout << "Enter a path: ";
	cin >> path;
	vector<string> dirs = split(path, ',');

	unordered_map<string, int> pathSteps;
	for (uint i = 0; i < dirs.size(); i++)
		pathSteps[dirs[i]]++;

	int totalSteps = 0;
	int neSteps = (pathSteps["ne"] - pathSteps["sw"]);
	int nSteps = (pathSteps["n"] - pathSteps["s"]);
	int nwSteps = (pathSteps["nw"] - pathSteps["se"]);

	totalSteps += abs(abs(neSteps) > abs(nwSteps) ? neSteps : nwSteps);
	totalSteps += (nSteps != 0) ? neSteps + nSteps : 0;
	//totalSteps += abs(abs(neSteps) > abs(nSteps) ? 0 : nSteps);

	cout << "The total number of steps required is: " << totalSteps << endl;


	return 0;
}

