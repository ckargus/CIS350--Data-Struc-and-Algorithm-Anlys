#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
// Curtis Kargus CIS 350 Program 4
//This program is meant to find the shorqueue distance to catch all unique Pokémon and end up back at
//where you start.The input starts off with an integer that represents how many Pokémon there are in
//the area.From there the user will put in the x and y coordinates of the Pokémon and the Pokémon’s
//name for example 5 6 evee meaning an evee is at x = 5 and y = 6. Once all Pokémon are entered it will
//give the user the shorqueue distance needed to catch all the unique Pokémon.The distance is calculated
//from just x and y movement not using A ^ 2 + B ^ 2 = C^2. So from point 2, 1 to 3, 4 the distance would be
//4 - 2 + 3 - 2 = 4.

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
struct LowestKeeper
{
	//post: makes a lower keeper with no data intalized
	LowestKeeper()
	{

	}
	// post: makes lower keepr with distance and name assigned a value
	LowestKeeper(int dis, string name)
	{
		distance = dis;
		this->name = name;
	}
	int distance;
	string name;
};
class PokeStop
{
public:
	// post: will make a pokestop with one ID added and one Pokemon added
	PokeStop(int location,string stop)
	{
		visitiedLocations.push_back(location);
		currentPoke.push_back(stop);
	}
	// post: assigns all variables from the parent variable to the current variable
	PokeStop(const PokeStop & parent)
	{
		visitiedLocations = parent.visitiedLocations;
		currentPoke = parent.currentPoke;
		currentDistance = parent.currentDistance;
		lowerBound = parent.lowerBound;
		
		
	}
	bool operator < (const PokeStop & lhs) const
	{
		return this->lowerBound > lhs.lowerBound;
	}
	// post: added a location and Pokemon to the current PokeStop
	void addLoction(int visited, string name)
	{
		currentPoke.push_back(name);
		visitiedLocations.push_back(visited);
	}
	// post: returns the value of the lower bound
	int GetLowerBound()
	{
		return lowerBound;
	}
	// post: returns the current distance of the pokestop
	int GetCurrentDistance()
	{
		return currentDistance;
	}
	// pre: intagers in the visited locations must be <= size of the array - 1
	//post: will calulate the current distace the Pokestop has based off of previous locations visited
	void CalulateCurrentDistance(const Matrix<int> & matrix, PokeStop & temp)
	{
		int disTemp = 0;
		for (int i = 0; i < temp.visitiedLocations.size() - 1; i++)
		{
			disTemp += matrix[visitiedLocations.at(i)][visitiedLocations.at(i+1)];
		}
		temp.currentDistance = disTemp;
	}
	// pre: vistited locations can't be empty and vistied locations must be intagers <= size of arry - 1
	// post: calulates the lower bound of the pokestop and sets lowerBound to it
	void CalulateLowerBound(const Matrix<int> & matrix, const vector<string> & key, PokeStop & stop)
	{
		int tempLowerBound = 0;
		int temp = INT_MAX;
		int postionInLowestValues = -1;
		bool found = false;
		LowestKeeper current;
		vector<LowestKeeper>  tempLowestValues;
		tempLowerBound += stop.currentDistance;
		for (int i = 0; i < matrix.numrows(); i++)
		{
			if (matrix[stop.visitiedLocations.back()][i] < temp && matrix[stop.visitiedLocations.back()][i] != -1)
			{
				temp = matrix[stop.visitiedLocations.back()][i];
			}
			
		}
		tempLowerBound += temp;
		for (int i = 0; i < matrix.numrows(); i++)
		{
			temp = INT_MAX;
			if (find(stop.currentPoke.begin(), stop.currentPoke.end(), key[i]) == stop.currentPoke.end())
			{
				for (int j = 0; j < matrix.numcols(); j++)
				{
					if (matrix[i][j] < temp && matrix[i][j] != -1)
					{
						temp = matrix[i][j];
					}
				}
				for (LowestKeeper x : tempLowestValues)
				{
					if (x.name == key[i])
					{
						found = true;
						if (x.distance > temp)
						{
							x.distance = temp;
						}
					}
				}
				if (found == false)
				{
					current.distance = temp;
					current.name = key[i];
					tempLowestValues.push_back(current);
				}
			}
		}
		for (LowestKeeper x : tempLowestValues)
		{
			tempLowerBound += x.distance;
		}
		stop.lowerBound = tempLowerBound;
	}
	//post: returns the vector of visited loctions
	vector<int> GetVistitedLocations()
	{
		return visitiedLocations;
	}
	// return the vetor of all the unique poke that have been caught
	vector<string> GetCurrentPoke()
	{
		return currentPoke;
	}
	
private:
	vector<int> visitiedLocations;
	vector<string> currentPoke;
	int currentDistance;
	int lowerBound;
};

struct point
{
	int x;
	int y;
};
//pre: key must repsent what pokemon are in each row and coloum. unique key must be a vector of all uniquie pokemon and sorted
// fullCircleKey is the unique is the same thing as unique key but with an extra orgin variable added
//post: creates the next nodes of the branch and bound algorithm and adds them to the priority queue
void Expand(priority_queue<PokeStop> & queue, const Matrix<int> & matrix, const vector<string> & key, const vector<string> & uniqueKey, const vector<string> & fullCircleKey)
{
	PokeStop best(queue.top());
	vector<string> currentPoke = best.GetCurrentPoke(); // space n
	sort(currentPoke.begin(), currentPoke.end()); // time n log n
	if (currentPoke == fullCircleKey)
	{
		return;
	}
	queue.pop();
	if (currentPoke == uniqueKey)
	{
		best.addLoction(0, "orgin");
		best.CalulateCurrentDistance(matrix, best);
		best.CalulateLowerBound(matrix, key, best);
		queue.push(best);
		return;
	}
	
	for (int i = 0; i < matrix.numrows(); i++) // n
	{
		if (find(currentPoke.begin(), currentPoke.end(), key[i]) == currentPoke.end()) // n
		{
			PokeStop temp(best);
			temp.addLoction(i, key[i]);
			temp.CalulateCurrentDistance(matrix,temp); // time n
			temp.CalulateLowerBound(matrix,key,temp); // time n^2 
			queue.push(temp);
		}
	}
}
int main()
{
	priority_queue<PokeStop> queue;
	vector<point> points;
	vector<string> key;
	vector<string> uniqueKey;
	vector<string> bestUniquePoke;
	vector<string> fullCircleKey;
	point temp;
	string name;
	PokeStop start(0,"orgin");
	key.push_back("orgin");
	uniqueKey.push_back("orgin");
	int size;
	cin >> size;
	Matrix<int> matrix(size + 1, size + 1);
	temp.x = 0;
	temp.y = 0;
	points.push_back(temp);
	for (int i = 0; i < size; i++)
	{
		cin >> temp.x;
		cin >> temp.y;
		cin >> name;
		points.push_back(temp);
		key.push_back(name);
		if (find(uniqueKey.begin(), uniqueKey.end(), name) == uniqueKey.end())
		{
			uniqueKey.push_back(name);
		}
	}
	sort(uniqueKey.begin(), uniqueKey.end());
	for (int i = 0; i < matrix.numcols(); i++)
	{
		for (int j = 0; j < matrix.numrows(); j++)
		{
			if (i == j)
			{
				matrix[i][j] = -1;
			}
			else
			{
				matrix[i][j] = abs(points[i].x - points[j].x) + abs(points[i].y - points[j].y);
			}
		}
	}
	start.CalulateLowerBound(matrix, key,start);
	start.CalulateCurrentDistance(matrix,start);
	queue.push(start);
	fullCircleKey = uniqueKey;
	fullCircleKey.push_back("orgin");
	sort(fullCircleKey.begin(), fullCircleKey.end());
	while (bestUniquePoke != fullCircleKey)
	{
		Expand(queue, matrix, key, uniqueKey,fullCircleKey);
		PokeStop poke(queue.top());
		bestUniquePoke = poke.GetCurrentPoke();
		sort(bestUniquePoke.begin(), bestUniquePoke.end());
	}
	PokeStop poke(queue.top());
	cout << poke.GetCurrentDistance() << endl;
	system("pause");
	return 0;
}