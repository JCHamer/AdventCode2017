#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	int numValid = 0;
	vector<int> totals;

	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	ifstream infile(argv[1]);
	string line;

	while (getline(infile, line))	{
		stringstream stream(line);
		vector<string> words;
		while(stream)	{
			string currWord;
			stream >> currWord;
			words.push_back(currWord);
		}

		bool validPhrase = true;
		for (uint i = 0; i < words.size(); i++)	{
			for (uint j = i+1; j < words.size(); j++)	{
				if (!words[i].compare(words[j]))	{
					validPhrase = false;
					break;
				}
			}
			if (!validPhrase)
				break;
		}
		if (validPhrase)
			numValid++;
	}

	cout << "Total number of valid passphrases = " << numValid << endl;

	return 0;
}
