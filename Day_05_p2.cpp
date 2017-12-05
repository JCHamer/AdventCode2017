#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	vector<int> jumps;

	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	ifstream infile(argv[1]);

	int curr;
	while (infile >> curr)	{
		jumps.push_back(curr);
	}

	int numSteps = 0;
	int pos = 0;

	while (pos >= 0 && (size_t)pos < jumps.size())	{
		if (jumps[pos] > 2)
			pos += jumps[pos]--;
		else
			pos += jumps[pos]++;
		numSteps++;
	}


	for (int i : jumps)
		cout << i << endl;

	cout << "Total numSteps = " << numSteps << endl;

	return 0;
}
