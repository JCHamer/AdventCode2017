#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string input;
	cin >> input;

	int sum = 0;

	for (int i = 0; i < input.size(); i++)	{
		if (input[i] == input[((i + (input.size() / 2))) % input.size()])
			sum+= input[i] - '0';
	}

	cout << "Total = " << sum << endl;

	return 0;
}
