/*
	Curtis Kargus CIS350 Project 1
	Program takes in a graph from user input. It does it by first taking in how many graphs the user
	will input followed by how big the graph is. The graphs can vary from size to size by inputting
	the size before the vertices. Then the vertices are added in the form of A 2 B C. A being the
	letter that is adjacent to B and C, and 2 being the number of vertices that A is adjacent to. The
	user does this until all vertices and their adjacent vertices are added. Once done the program will
	order the vertices so that each vertex is as close as possible to its adjacent vertices then displays
	it on screen. The number at the end of this list is the biggest distance a vertex is away from
	adjacent vertex, distance being how many characters away it is. Will do this for each graph.

*/


#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
template <class Object>
class Matrix
{
public:
	//Pre: rows and cols are assigned
	//	rows and cols are non-negative
	// Post: a matrix of size rows by cols is made
	Matrix(int rows = 1, int cols = 1) : array(rows)
	{
		for (int i = 0; i < rows; i++)
			array[i].resize(cols);
	}
	//Pre: rows and cols are assigned
	//	rows and cols are non-negative
	// Post: matrix will be a new size of rows by cols
	void resize(int rows, int cols)
	{
		array.resize(rows);
		for (int i = 0; i < rows; i++)
		{
			array[i].resize(cols);
		}
	}
	//Pre: row is assigned
	//	row is non-negative
	//Post: returns value that is the place row
	const vector<Object> & operator[](int row) const 
	{
		return array[row];
	}
	//Pre: row is assigned
	//	row is non-negative
	//Post: returns value that is the place row
	vector<Object> & operator[](int row) 
	{
		return array[row];
	}
	//Post: returns the size of the row in the matrix
	int numrows() const 
	{
		return array.size();
	}
	//Post: returns the number of cols in matrix
	int numcols() const
	{
		return numrows() ? array[0].size() : 0;
	}
private:
	vector< vector<Object> > array;
};

class Graph
{
public:
	//Pre: size is assigned
	//	size is non-negative
	//Post: adj is assigned to matrix of size by size
	Graph(int size) // creates an empty graph with size vertices 
	{
		Matrix<char> temp(size, size);
		adj = temp;
		this->size = size;
	}
	//Pre: users must add the same number of points as the size
	//Post: adj will be filled
	void fillGraph()// fills in the graph from cin 
	{
		int row = 0;
		int col = 0;
		int temp = 0; // how many ? I need
		while (col < size)
		{
			cin >> adj[col][row];
			row++;
			cin >> temp;
			for (int i = 0; i < temp; i++)
			{
				cin >> adj[col][row];
				row++;
			}
			temp = size - temp;
			for (int i = 1; i < temp; i++)
			{
				adj[col][row] = '?';
				row++;
			}
			row = 0;
			col++;
		}
	}//Pre: adj must be filled
	//Post: displays the contents of adj to the screen
	void printGraph() // prints the graph (for debugging only) 
	{
		cout << endl;
		int row = size;
		int col = size;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cout << adj[j][i];
				cout << " ";
			}
			cout << endl;
		}

	}
	//Pre: order is assigned
	//	order must contatin the same characters as the first row of adj
	//Post: returns the max cover of the order
	int maxCover( const vector<char> & order)// returns the maxCover for the ordering order
	{		
		int max = 0;
		int temp;
		for (int i = 0; i < size; i++)
		{
			temp = cover(order[i], order);
			if (temp > max)
			{
				max = temp;
			}
		}
		return max;
	}
	//Pre: vertex and order are assigned
	//	vertex must be a character that is in adj's first row
	//	order must contain the same characters as adj's first row
	//Post: returns the largest cover of the vertex
	int cover(char vertex,   const vector<char> & order) // returns the cover size for vertex 
	{
		int cover = 0;
		int currentVertexColMat = 0;
		while (adj[currentVertexColMat][0] != vertex)
		{
			currentVertexColMat++;
		}
		int vertexPosVect = 0;
		int nearPosVect = 0;
		int nearRow = 0;
		char near = adj[currentVertexColMat][nearRow]; // adj to vertex
		char temp = order[0]; //holds which cahracter im at in search
		while (near != '?')
		{
			while (temp != vertex)
			{
				temp = order[vertexPosVect];
				if (temp == vertex)
					break;
				vertexPosVect++;
			}
			temp = order[0]; // make search starts from begining of order again
			while (temp != near)
			{
				
				temp = order[nearPosVect];
				if (temp == near)
					break;
				nearPosVect++;
			}
			if (cover < abs(nearPosVect - vertexPosVect))
			{
				cover = abs(nearPosVect - vertexPosVect);
			}
			nearRow++;
			if (nearRow == size)
			{
				break;
			}
			near = adj[currentVertexColMat][nearRow];
			nearPosVect = 0;
			vertexPosVect = 0;
			temp = order[0];
		}
		return cover;
		}
	//Pre: adj must be filled
	//Post: key gets set to first row of adj
	vector<char> ReturnKey() 
	{
		vector<char> key(size);
		for (int i = 0; i < size; i++)
		{
			key[i] = adj[i][0];
		}
		return key;
	}
private:
	int size;
	Matrix<char> adj;
};

int main()
{
	vector<char> order;
	vector<char> bestOrder;
	int min;
	int max;
	int size;
	int numGraphs;
	cin >> numGraphs;
	for (int i = 0; i < numGraphs; i++)
	{
		cin >> size;
		Graph test(size);
		min = size + 1;
		test.fillGraph();
		order = test.ReturnKey();
		sort(order.begin(), order.end());
		do
		{
			max = test.maxCover(order);
			if (max < min)
			{
				min = max;
				bestOrder = order;
			}
		} while (next_permutation(order.begin(), order.end()));
		for (char x : bestOrder)
		{
			cout << x << " ";
		}
		cout << min << endl;
	}
	//system("Pause");
	return 0;
	system("pause");
}