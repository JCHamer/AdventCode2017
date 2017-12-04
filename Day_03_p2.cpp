#include <iostream>
#include <deque>

using namespace std;

void printGrid(deque<deque<int>> grid);
int getSum(deque<deque<int>> grid, uint i, uint j, uint diam);

int main()
{
	//int sum = 0;
	int desired;

	deque<deque<int>> grid(1, deque<int> (1,0));

	cout << "Enter wanted address: ";
	cin >> desired;

	int num = 1;
	uint i = 0, j = 0;
	grid[i][j++] = num++;

	/*
	 * Build the spiralized data
	 */
	unsigned int diam = 1;	// current diameter of the spiral, increases by 2 each time 
	bool stop = false;
	int res = 0;
	while (1)	{
		// Update the diameter to now be one spiral farther out
		// Additionally, enlarge the deques to hold the data
		diam += 2;
		for (uint x = 0; x < grid.size(); x++)	{
			grid[x].push_front(0);
			grid[x].push_back(0);
		}
		grid.push_front(deque<int> (diam, 0));
		grid.push_back(deque<int> (diam, 0));
		// increment i and j as the spiral is now bigger and they stay centered
		i++;
		j++;

		// From entry to outer ring, 1 from buttom up to one below top right corner
		for (uint x = 0; x < diam - 2; x++)	{
			res = getSum(grid, i, j, diam);
			grid[i][j] = res;
			if (grid[i--][j] > desired)	{
				stop = true;
				break;
			}

		}
		if (stop)
			break;

		// From top right across to one before top left corner
		for (uint x = 0; x < diam - 1; x++)	{
			res = getSum(grid, i, j, diam);
			grid[i][j] = res;
			if (grid[i][j--] > desired)	{
				stop = true;
				break;
			}
		}
		if (stop)
			break;

		// From top left down to one before bottom left corner
		for (uint x = 0; x < diam - 1; x++)	{
			res = getSum(grid, i, j, diam);
			grid[i][j] = res;
			if (grid[i++][j] > desired)	{
				stop = true;
				break;
			}
		}
		if (stop)
			break;

		// From bottom left across to bottom right corner
		for (uint x = 0; x < diam; x++)	{
			res = getSum(grid, i, j, diam);
			grid[i][j] = res;
			if (grid[i][j++] > desired)	{
				stop = true;
				break;
			}
		}
		if (stop)
			break;
	}

	printGrid(grid);

	/*
	 * Determine the Manhattan Distance to the center of the requested num
	 */
	/*pair<uint, uint> loc(diam - 1, diam - 1);	//loc(i,j)
	while (grid[loc.first][loc.second] != desired)	{
		if (desired > grid[loc.first][loc.second])	{
			if (loc.second == 0)	{	// On left edge
				(loc.first < diam - 1) ? loc.first++ : loc.second++;
			}
			else if (loc.first == diam - 1)	{	// On bottom edge
				(loc.second < diam - 1) ? loc.second++ : loc.first--;
			}
			else if (loc.second == diam - 1)	{	// On right edge
				(loc.first > 0) ? loc.first-- : loc.second--;
			}
			else if (loc.first == 0)	{	// On top edge
				(loc.second > 0) ? loc.second-- : loc.first++;
			}
		}
		else if (desired < grid[loc.first][loc.second])	{
			if (loc.second == 0)	{	// On left edge
				(loc.first > 0) ? loc.first-- : loc.second++;
			}
			else if (loc.first == diam - 1)	{	// On bottom edge
				(loc.second > 0) ? loc.second-- : loc.first--;
			}
			else if (loc.second == diam - 1)	{	// On right edge
				(loc.first < diam - 1) ? loc.first++ : loc.second--;
			}
			else if (loc.first == 0)	{	// On top edge
				(loc.second < diam - 1) ? loc.second++ : loc.first++;
			}
		}
	}

	// At this point loc(i,j) holds the location of the required number
	sum += (loc.first > diam/2) ? loc.first - diam/2 : diam/2 - loc.first;
	sum += (loc.second > diam/2) ? loc.second - diam/2 : diam/2 - loc.second;
	*/

	//cout << "Total number of steps is " << sum << endl;
	cout << "First value larger than your input is " << res << endl;

	return 0;
}

int getSum(deque<deque<int>> grid, uint i, uint j, uint diam)	{
	int total = 0;
	for (int x = -1; x < 2; x++)	{
		for (int y = -1; y < 2; y++)	{
			if (((int)i+x >= 0) && ((int)i+x < (int)diam) && ((int)j+y >= 0) && ((int)j+y < (int)diam) && grid[(uint)((int)i+x)][(uint)((int)j+y)] != 0)
				total += grid[(uint)((int)i+x)][(uint)((int)j+y)];
		}
	}
	return total;
}

void printGrid(deque<deque<int>> grid)	{
	for (deque<int> line : grid)	{
		for (int elt : line)
			cout << elt << "\t";
		cout << endl;
	}
}
