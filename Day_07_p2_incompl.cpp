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

	for (node * child : root->children)	{
		child->childrenWeight = assignChildWeights(child);
		total += child->childrenWeight + child->weight;
	}

	if (root->children.size() > 2)	{
		if ((root->children[0]->childrenWeight + root->children[0]->weight) != (root->children[1]->childrenWeight + root->children[1]->weight))	{
			cout << "Use correct weight of: " << root->children[2]->childrenWeight + root->children[2]->weight << endl;
		}
		else	{
			int compWeight = root->children[0]->childrenWeight + root->children[0]->weight;
			for (uint i = 2; i < root->children.size(); i++)	{
				if (compWeight != (root->children[i]->childrenWeight + root->children[i]->weight))	{
					cout << "Use correct weight of: " << compWeight << endl;
				}
			}
		}
	}


	return total;
}

