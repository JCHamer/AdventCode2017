#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string input;
	cin >> input;

	int sum = 0;

	for (int i = 0; i < input.size() - 1; i++)	{
		if (input[i] == input[i+1])
			sum+= input[i] - '0';
	}
	
	if (input[input.size() - 1] == input[0])
		sum+= input[input.size() - 1] - '0';

	cout << "Total = " << sum << endl;

	return 0;
}
