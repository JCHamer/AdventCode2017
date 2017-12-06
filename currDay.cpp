#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	int numSteps = 0;
	vector<double> prevStates;
	vector<uint> buckets;

	ifstream infile(argv[1]);
	string line;
	while (getline(infile, line))	{
		stringstream stream(line);
		while(stream)	{
			uint num;
			stream >> num;
			buckets.push_back(num);
		}
	}

	double acc = 0;
	for (uint x = 0; x < buckets.size(); x++)
		acc += buckets[x] * (pow(2,(buckets.size() - x - 1)));

	cout << "Total Sum = " << sum << endl;

	return 0;
}
