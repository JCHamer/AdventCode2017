#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	ifstream infile(argv[1]);
	vector<uint> pipes;	//index <groupID>

	string line;
	while (getline(infile, line))	{
		stringstream stream(line);
		uint groupID;
		stream >> groupID;
		string trash;
		stream >> trash;
		string currNum;
		while(stream >> currNum)	{
			if (currNum[currNum.size() - 1] == ',')
				currNum = currNum.substr(0,currNum.size() - 1);
			uint num = (uint)stoi(currNum);

			if ((int)num - 1 > (int)pipes.size())	{
				pipes.push_back((uint)pipes.size());
				while (pipes.size() - 1 < (uint)num)
					pipes.push_back((uint)pipes.size());
			}

			if (pipes[num] > (uint)groupID)	{
				pipes[num] = (uint)groupID;
			}
		}
	}

	int count = 0;
	for (uint x : pipes)	{
		if (x == 0)
			count++;
	}

	cout << "Total number of programs in the group 0: " << count << endl;

	return 0;
}
