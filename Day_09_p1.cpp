#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	vector<string> groups;
	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	ifstream infile(argv[1]);
	string group;
	while (infile >> group)
		groups.push_back(group);

	group = groups[0];
	uint groupCount = 0;

	bool inGarbage = false;
	uint x = 0;	// position in string
	uint score = 0;

	while (x < group.size())	{
		if (inGarbage)	{
			if (group[x] == '>')
				inGarbage = false;
			if (group[x] == '!')	{
				x += 2;
				continue;
			}
			x++;
			continue;
		}


		if (group[x] == '<')	{
			inGarbage = true;
		}

		if (group[x] == '{')	{
			groupCount++;
		}

		if (group[x] == '}')	{
			score += groupCount;
			groupCount--;
		}

		x++;
	}

	cout << "Total score was: " << score << endl;

	return 0;
}
