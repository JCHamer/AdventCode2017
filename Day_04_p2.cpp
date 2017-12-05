#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
unordered_map<char, size_t> getLetterCounts(string word);

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
			auto iWord = getLetterCounts(words[i]);
			for (uint j = i+1; j < words.size(); j++)	{
				auto jWord = getLetterCounts(words[j]);
				if (iWord == jWord)	{
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

unordered_map<char, size_t> getLetterCounts(string word)	{
	unordered_map<char, size_t> letterCounts;
	for (char let : word)
		letterCounts[let]++;

	return letterCounts;
}

