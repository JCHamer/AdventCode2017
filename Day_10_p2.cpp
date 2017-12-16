#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

const uint LISTSIZE = 256;

int main()
{
	vector<uint> list;
	list.reserve(LISTSIZE);
	for (uint i = 0; i < LISTSIZE; i++)
		list.push_back(i);
	uint currPos = 0, skipSize = 0;

	string lengthSeq;
	cout << "Enter sequence of lengths: ";
	cin >> lengthSeq;

	vector<uint> lengths;
	for (char num : lengthSeq)
		lengths.push_back((uint)num);
	lengths.push_back(17);
	lengths.push_back(31);
	lengths.push_back(73);
	lengths.push_back(47);
	lengths.push_back(23);

	for (uint x = 0; x < 64; x++)	{
		for (uint i = 0; i < lengths.size(); i++)	{
			uint start = currPos;
			uint end = (currPos + lengths[i] - 1) % LISTSIZE;
			uint count = 0;
			while (count++ < lengths[i] / 2)	{
				uint tmp = list[start];
				list[start] = list[end];
				list[end] = tmp;

				if(start == list.size() - 1)
					start = 0;
				else
					start++;

				if(end == 0)
					end = (uint)list.size() - 1;
				else
					end--;
			}

			currPos = (currPos + lengths[i] + skipSize)%LISTSIZE;
			skipSize++;
		}
	}

	vector<uint> denseHash;
	for (uint i = 0; i < 16; i++)	{
		uint currRes = 0;
		for (uint j = 0; j < 16; j++)	{
			currRes ^= list[(16*i) + j];
		}
		denseHash.push_back(currRes);
		if (currRes < 16)
			cout << '0';
		cout << hex << currRes;
	}
	cout << endl;

	/*for (uint x : list)
		cout << x << " ";
	cout << endl;*/


	return 0;
}

