/*
Curtis Kargus CIS 350
Program computes for a company the minimum number of employees that 
need to ask for a raise for everyone in the company to get a raise. 
Each employee has one boss and a boss will only request a raise if 
more than x% of his employees ask for a raise. Once then owner gets
all the requests for a raise if the number of his immediate employees
who asked for a raise is greater that x% then everyone in the company
gets a raise. The input is done in two lines first lines says how many
employees are in the company not includingthe boss and the next number
says what the x% is. The second line is a list of the employees and who
is there boss the integer entered says who they work for and the position
in the list starting at 1 states who they are.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Node
{
	int id;
	int minRequests4Raise;
	vector<Node *> underlings;
	// post: creates node and sets id equal to n
	Node(int n = 0)
	{
		id = n;
		minRequests4Raise;
	}
};
//Post: makes a new child node to the parent node
void addUnderling(Node * ptr, int id)
{
	ptr->underlings.push_back(new Node(id));
}
//post: makes the underPtr the child of ptr
void addUnderling(Node * ptr, Node *underPtr)
{
	ptr->underlings.push_back(underPtr);
}
class Tree
{
private:
	Node * root;
	//pre: all nodes in tree must have an assiged id and level is no less than 0 and ptr is the root node of tree
	//post: prints the tree with indentations indicating what nodes are connected with a parent child relationship
	void print(Node * ptr, int level)
	{
		if (ptr == nullptr)
		{
			return;
		}
		for (int i = 0; i < level * 3; i++)
		{
			cout << " ";
		}
		cout << ptr->id << endl;
		for (Node * x : ptr->underlings)
		{
			print(x, level + 1);
		}
	}
	// pre: root is the root of the tree
	// post: returns the target node if the node is in the tree otherwise returns nullptr
	Node * find(Node * root, int target)
	{
		Node * found = nullptr;
		if (root == nullptr)
		{
			return nullptr;
		}
		if (root->id == target)
		{
			return root;
		}
		for (Node * x : root->underlings)
		{
			found = find(x, target);
			if (found != nullptr)
			{
				return found;
			}
			
		}
		return found;
	}
	// pre: percent must be postive and no greater than 1 and root is the root of the tree
	// post: all minRaises are set for each node and the minRaise for the entire tree will be returned.
	int minRaise(Node * root, double percent)
	{
		vector<int> underlingsMinRasies;
		double minNumNeeded;
		root->minRequests4Raise = 0;
		if (root->underlings.size() == 0)
		{
			root->minRequests4Raise = 1;
		}
		else if (root->underlings.size() != 0)
		{
			for (Node * x : root->underlings)
			{
				underlingsMinRasies.push_back(minRaise(x, percent));
			}
			sort(underlingsMinRasies.begin(), underlingsMinRasies.end());
			minNumNeeded = ceil(underlingsMinRasies.size() * percent);
			for (int i = 0; i < minNumNeeded; i++)
			{
				root->minRequests4Raise += underlingsMinRasies[i];
			}
		}
		return root->minRequests4Raise;
	}
public:
	//post: sets the tree's root node to rt
	Tree(Node * rt = nullptr) { root = rt; }
	// post: sets the trees root to a new node with the id of id
	Tree(int id)
	{
		root = new Node(id);
	}
	//post: returns the root node of the tree
	Node * getRoot()
	{
		return root;
	}
	//pre: all nodes in tree must have an assiged id
	//post: prints the tree with indentatins indicating what nodes are connected with a parent child relationship
	void printTree()
	{
		print(this->root, 0);
	}
	// post: returns the target node if the node is in the tree otherwise returns nullptr
	Node * find(int target)
	{
		return find(this->root, target);
	}
	//pre: percent must be greater than zero and less than or equal to 1
	// post: all minRaises are set for each node and the minRaise for the entire tree will be returned.
	int minRaise(double percent)
	{
		return minRaise(getRoot(), percent);
	}
};
class Forest
{
private:
	vector<Tree> trees;
public:
	// pre: pecent must be greater than 0 and no grater than 1
	// post: all minRaises are set for each node and the minRaise for the first tree will be returned.
	int minRaise(double percent)
	{
		return trees[0].minRaise(percent);
	}
	// post: creates forest with one tree that contains one node with id 0
	Forest()
	{
		Node * owner = new Node(0);
		Tree ownersTree(owner);
		trees.push_back(ownersTree);
	}
	//post: gets rid of all tress in the forest then puts back in one tree with one node of id 0
	void clear()
	{
		trees.clear();
		Node * owner = new Node(0);
		Tree ownersTree(owner);
		trees.push_back(ownersTree);
	}
	// post: displays all tress in the forest with the tree print format
	void print()
	{
		for (Tree x : trees)
		{
			x.printTree();
		}
	}
	// post: returns node with target id if that node is in the forest otherwise returns nullptr
	Node * find(int target)
	{
		Node * found = nullptr;
		for (Tree x : trees)
		{
			found = x.find(target);
			if (found != nullptr)
			{
				return found;
			}
		}
		return found;
	}
	// pre: boss must be equal to or greaater than zero and underling must be greater than zero
	// also boss != underling
	//post: if underling or boss is not in the forest they will be added to the forest 
	//if they are in the forest then boss will be connected to the underling.
	void insert(int boss, int underling)
	{
		Node * bossPtr = find(boss);
		Node * underPtr = find(underling);
		if (bossPtr == nullptr && underPtr == nullptr) // need a new tree
		{
			trees.push_back(Tree(boss));
			addUnderling(trees[trees.size() - 1].getRoot(), underling);
		}
		else if (underPtr == nullptr)
		{
			addUnderling(bossPtr, underling);
		}
		else if (underPtr != nullptr) // the underling is already a boss
		{
			if (bossPtr == nullptr)  // if boss is not in the tree put him in
			{
				trees.push_back(Tree(boss));
				bossPtr = find(boss);
			}
			// now both are in the tree 
			addUnderling(bossPtr, underPtr);
			for (auto itr = trees.begin(); itr != trees.end(); itr++)
				if (itr->getRoot()->id == underling)
				{
					trees.erase(itr);
					return;
				}

		}
	}
};
int main()
{
	Forest test;
	int empolyees;
	int boss;
	double percent;
	int minNum;
	cin >> empolyees;
	cin >> percent;
	percent /= 100.00;
 	while (empolyees != 0 && percent != 0)
	{

		for (int i = 1; i < empolyees + 1; i++) // tn^2
		{
			cin >> boss;
			test.insert(boss, i);
		}
		test.print(); //tn
		minNum = test.minRaise(percent); // n logn
		cout << minNum <<endl;
		test.clear();
		cin >> empolyees;
		cin >> percent;
		percent /= 100.00;
	}
	//system("pause");
	return 0;
}