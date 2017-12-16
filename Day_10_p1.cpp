#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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

	stringstream stream(lengthSeq);
	uint num;
	vector<uint> lengths;
	while (stream >> num)	{
		lengths.push_back(num);
		if (stream.peek() == ',')
			stream.ignore();
	}

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

	for (uint x : list)
		cout << x << " ";
	cout << endl;

	cout << "The product of the first two list elemtents is : " << list[0]*list[1] << endl;


	return 0;
}

