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

	int numSteps = 1;
	vector<double> prevStates;
	vector<uint> buckets;
	bool hit = false;

	ifstream infile(argv[1]);
	uint num;
	while (infile >> num)	{
		buckets.push_back(num);
	}

	double acc = 0;
	for (uint x = 0; x < buckets.size(); x++)
		acc += buckets[x] * (pow(10,(buckets.size() - x - 1)));
	prevStates.push_back(acc);

	while (true)	{
		uint pos = 0;
		for (uint i = 1; i < buckets.size(); i++)	{
			if (buckets[i] > buckets[pos])
				pos = i;
		}

		uint numToDist = buckets[pos];
		buckets[pos++] = 0;
		for (; numToDist > 0; numToDist--)	{
			if (pos >= buckets.size())
				pos = 0;
			buckets[pos++]++;
		}

		double acc = 0;
		for (uint x = 0; x < buckets.size(); x++)
			acc += buckets[x] * (pow(10,(buckets.size() - x - 1)));
		bool match = false;
		for (double x : prevStates)	{
			if (x == acc)
				match = true;
		}
		if (match && !hit)	{
			hit = true;
			prevStates.clear();
			numSteps = 0;
		}
		else if (match && hit)
			break;
		prevStates.push_back(acc);
		numSteps++;

	}

	cout << "Total number of steps = " << numSteps << endl;

	return 0;
}
