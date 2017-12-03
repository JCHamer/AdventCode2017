#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

int main(int argc, char *argv[])
{
	int sum = 0;
	vector<int> diffs;

	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	ifstream infile(argv[1]);
	string line;

	while (getline(infile, line))	{
		stringstream stream(line);
		int max = INT_MIN, min = INT_MAX;
		while(stream)	{
			int num;
			stream >> num;

			min = std::min(min, num);
			max = std::max(max, num);
		}

		// Add diff of max and min to diffs vector
		diffs.push_back(max - min);
	}

	for (int i : diffs)
		sum+=i;

	cout << "Total Diff = " << sum << endl;

	return 0;
}
