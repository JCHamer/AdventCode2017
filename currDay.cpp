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
	uint num;
	while (infile >> num)	{
		buckets.push_back(num);
	}

	double acc = 0;
	for (uint x = 0; x < buckets.size(); x++)
		acc += buckets[x] * (pow(2,(buckets.size() - x - 1)));
	prevStates.push_back(acc);

	while (true)	{
		uint pos = 0;
		for (uint i = 0; i < buckets.size(); i++)	{
			if (buckets[i] > buckets[pos])
				pos = i;
		}

		uint numToDist = buckets[pos++];
		for (; numToDist > 0; numToDist--)	{
			if (pos >= buckets.size())
				pos = 0;
			buckets[pos] = numToDist;
		}

		double acc = 0;
		for (uint x = 0; x < buckets.size(); x++)
			acc += buckets[x] * (pow(2,(buckets.size() - x - 1)));
		bool match = false;
		for (double x : prevStates)	{
			if (x == acc)
				match = true;
		}
		if (match)
			break;
		prevStates.push_back(acc);
		numSteps++;

	}

	cout << "Total number of steps = " << numSteps << endl;

	return 0;
}
