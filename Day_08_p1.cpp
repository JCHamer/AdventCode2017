#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int main(int argc, char *argv[])
{
	unordered_map<string, int> regFile;

	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	ifstream infile(argv[1]);

	string destReg, dir, sourceReg, comp, trash;
	int num, compNum;
	while (infile >> destReg >> dir >> num >> trash >> sourceReg >> comp >> compNum)	{
		if (comp == "<" && regFile[sourceReg] < compNum)
			regFile[destReg] = (dir[0] == 'i') ? regFile[destReg] + num : regFile[destReg] - num;
		else if (comp == ">" && regFile[sourceReg] > compNum)
			regFile[destReg] = (dir[0] == 'i') ? regFile[destReg] + num : regFile[destReg] - num;
		else if (comp == "<=" && regFile[sourceReg] <= compNum)
			regFile[destReg] = (dir[0] == 'i') ? regFile[destReg] + num : regFile[destReg] - num;
		else if (comp == ">=" && regFile[sourceReg] >= compNum)
			regFile[destReg] = (dir[0] == 'i') ? regFile[destReg] + num : regFile[destReg] - num;
		else if (comp == "==" && regFile[sourceReg] == compNum)
			regFile[destReg] = (dir[0] == 'i') ? regFile[destReg] + num : regFile[destReg] - num;
		else if (comp == "!=" && regFile[sourceReg] != compNum)
			regFile[destReg] = (dir[0] == 'i') ? regFile[destReg] + num : regFile[destReg] - num;
	}

	pair<string, int> currMax;
	for (auto it = regFile.begin(); it != regFile.end(); it++)	{
		if (it->second > currMax.second)	{
			currMax.first = it->first;
			currMax.second = it->second;
		}
	}

	cout << "Max register value = " << currMax.second << endl;

	return 0;
}
