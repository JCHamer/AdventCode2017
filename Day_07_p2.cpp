#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

struct node	{
	string name;
	vector<node*> children;
	int weight, childrenWeight;
};

node* findNode(string name, vector<node*> nodes);
void deleteTree(vector<node*>);
int assignChildWeights(node* root);
void findWeightDiff(node *start, node* parent, uint childNum);

int main(int argc, char *argv[])
{
	vector<int> totals;

	if (argc != 2)	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	ifstream infile(argv[1]);
	string line;

	vector <node*> nodesToBeLinked;

	while (getline(infile, line))	{
		stringstream stream(line);
		string name, weight;
		stream >> name >> weight;

		node* nodeToFill= findNode(name, nodesToBeLinked);
		if (nodeToFill != nullptr)	// found the node
			nodeToFill->weight = stoi(weight.substr(1, weight.size() - 2));
		else	{
			nodeToFill = new node;
			nodeToFill->name = name;
			nodeToFill->weight = stoi(weight.substr(1, weight.size() - 2));
			nodesToBeLinked.push_back(nodeToFill);
		}

		string child;
		stream >> child;
		while(stream >> child)	{
			if (child[child.size() - 1] == ',')
				child = child.substr(0, child.size() - 1);
			node* childFound = findNode(child, nodesToBeLinked);
			if (childFound != nullptr)	{	// found the node
				nodeToFill->children.push_back(childFound);
				for (uint i = 0; i < nodesToBeLinked.size(); i++)	{
					if (childFound == nodesToBeLinked[i])
						nodesToBeLinked.erase(nodesToBeLinked.begin() + i);
				}
			}
			else	{
				childFound = new node;
				childFound->name = child;
				childFound->weight = -1;
				nodeToFill->children.push_back(childFound);
			}
		}

	}

	// There will only be one node left and it is the root
	assert(nodesToBeLinked.size() == 1);

	// Go through the tree recursively setting up the children weights
	assignChildWeights(nodesToBeLinked[0]);


	cout << "The root element is named: " << nodesToBeLinked[0]->name << endl;

	deleteTree(nodesToBeLinked);

	return 0;
}

node* findNode(string name, vector<node*> nodes)	{
	queue<node*> nodeQueue;
	for (uint i = 0; i < nodes.size(); i++)	{
		nodeQueue.push(nodes[i]);
		if (nodes[i]->name == name)
			return nodes[i];
	}

	while (!nodeQueue.empty())	{
		if (!nodeQueue.front()->children.empty())	{
			for (node *x : nodeQueue.front()->children)	{
				nodeQueue.push(x);
				if (x->name == name)	{
					return x;
				}
			}
		}
		nodeQueue.pop();
	}

	return nullptr;
}

void deleteTree(vector<node*> nodes)	{
	queue<node*> nodesToDel;
	for (node* x : nodes)	{
		nodesToDel.push(x);
	}

	while (!nodesToDel.empty())	{
		if (!nodesToDel.front()->children.empty())	{
			for (node *x : nodesToDel.front()->children)
				nodesToDel.push(x);
		}
		delete nodesToDel.front();
		nodesToDel.pop();
	}
}

int assignChildWeights(node* root)	{
	int total = 0;

	for (uint i = 0; i < root->children.size(); i++)	{
		root->children[i]->childrenWeight = assignChildWeights(root->children[i]);
		total += root->children[i]->childrenWeight + root->children[i]->weight;
	}

	for (uint i = 0; i < root->children.size(); i++)	{
		findWeightDiff(root->children[i], root, i);
	}


	return total;
}

void findWeightDiff(node *start, node* parent, uint childNum)	{
	// Find the total weight that this node and its children should weigh
	int weight;
	if (childNum > 0)
		weight = parent->children[childNum-1]->childrenWeight + parent->children[childNum-1]->weight;
	else if (parent->children.size() > 1)
		weight = parent->children[1]->childrenWeight + parent->children[1]->weight;
	else	{
		cout << "branch with only 1 child" << endl;
		exit (-1);
	}
	weight -= start->weight;

	int check  = -1;
	for (uint i = 0; (int)i < (int)start->children.size(); i++)	{
		if ((start->children[i]->childrenWeight + start->children[i]->weight) != weight/(int)start->children.size())	{
			check = (int)i;
		}
	}

	if (check == -1)
		return;

//	node *child1 = start->children[(uint)check];
//	node *child2 = start->children[(uint)check + 1];

	int corrWeight = start->weight + weight - start->childrenWeight;

	/*
	 *First output for when the mistake is an inner node, it will be output from the first line
	 *Last output for when the mistake comes from a leaf, it will be output from the second line
	 */
	cout << "Correct branch weight is: " << corrWeight << endl;	
	cout << "Correct branch weight is: " << weight / (int)start->children.size() << endl;

	

	
}
