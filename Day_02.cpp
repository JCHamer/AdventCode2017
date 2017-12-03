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
	vector<int> totals;

	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	ifstream infile(argv[1]);
	string line;

	while (getline(infile, line))	{
		stringstream stream(line);
		vector<int> lineNums;
		while(stream)	{
			int num;
			stream >> num;
			lineNums.push_back(num);
		}

		int quotient = -1;
		for (int i = 0; i < lineNums.size(); i++)	{
			for (int j = 0; j < lineNums.size(); j++)	{
				if (lineNums[i] > lineNums[j] && lineNums[i]%lineNums[j] == 0)	{
					quotient = lineNums[i]/lineNums[j];
					break;
				}
			}
			if (quotient != -1)
				break;
		}

		// Add quotient to totals vector
		totals.push_back(quotient);
	}

	for (int i : totals)
		sum+=i;

	cout << "Total Sum = " << sum << endl;

	return 0;
}
