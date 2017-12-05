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

	for (int i : jumps)
		cout << i << endl;

	//cout << "Total Sum = " << sum << endl;

	return 0;
}
