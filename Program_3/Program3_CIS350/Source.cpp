#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
using namespace std;

//Curtis Kargus
//Program is meant to determine if all points on a flat plane also known as stations will all be connected in
//some way to one another if each station only connects to the two closets.If they are all connected in
//some way then the program will print out yes otherwise it will print out no.putting stations into the
//program is done by first inputting the number of stations followed by that many sets of coordinate
//points in the form of 0 0 which would represent the origin on the plane.From there the user can keep
//doing this for as many planes as they want and when they wish to end the program enter 0 for the
//number of points.

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


class Station
{
private:
	int myId;
	double x;
	double y;
	Station * connected1 = nullptr;
	double connected1Dis;
	Station * connected2 = nullptr;
	double connected2Dis;
	//post: returns which station is the west most if they are the same amount west most
	// then will return the one that is south most if the are equal amount west and south most will return the left 
	//prameter
	Station * LeftMost(Station * right, Station * left)
	{
		if (right->x < left->x)
		{
			return right;
		}
		else if(right->x == left->x)
		{
			if (right->y < left->y)
			{
				return right;
			}
			else
			{
				return left;
			}
		}
		else
		{
			return left;
		}
	}
public:
	//post: will return the ID of the "left" connected station else will return -1
	int GetConnected2ID()
	{
		if (connected2 == nullptr)
			return -1;
		return connected2->myId;
	}
	// will return the ID of the "right" connected station else will return -1
	int GetConnected1ID()
	{
		if (connected1 == nullptr)
			return -1;
		return connected1->myId;
	}
	// return ID of the station
	int GetId()
	{
		return myId;
	}
	// pre all id's must be postive or zero\
	// post will establish a nodes id, x-cord,and y-cord
	Station(int id, double x, double y)
	{
		myId = id;
		this->x = x;
		this->y = y;
		connected1Dis = -1;
		connected2Dis = -1;
	}
	// post: make the currect station connected to another station
	// if the other station is closer or if the distance is the same whoever is the west most
	// if equal west most then will take the south most
	// otherwie is will not connect the current staion to the other station
	void CalulateNeighbor( Station * ptr)
	{
		Station * leftMost = nullptr;
		Station * rightMost = nullptr;
		double diffX;
		double diffY;
		double distance;
		if (ptr == nullptr)
		{
			return;
		}
		diffX = x - ptr->x;
		diffY = y - ptr->y;
		distance = pow(diffX, 2) + pow(diffY, 2);
		if (connected1Dis < 0)
		{
			connected1Dis = distance;
			connected1 = ptr;
			return;
		}
		else if (connected2Dis < 0)
		{
			connected2Dis = distance;
			connected2 = ptr;
			return;
		}
		else if (connected1Dis > connected2Dis && connected1Dis >= distance)
		{
			if (abs(distance - connected1Dis) < 0.0000001)
			{
				leftMost = LeftMost(connected1, ptr);
				if (leftMost->GetId() == ptr->GetId())
				{
					connected1Dis = distance;
					connected1 = ptr;
				}

			}
			else
			{
				connected1Dis = distance;
				connected1 = ptr;
			}
		}
		else if (connected2Dis > connected1Dis && connected2Dis >= distance)
		{

			if (abs(distance - connected2Dis) < 0.0000001)
			{
				leftMost = LeftMost(connected1, ptr);
				if (leftMost->GetId() == ptr->GetId())
				{
					connected2Dis = distance;
					connected2 = ptr;
				}
			}
			else
			{
				connected2Dis = distance;
				connected2 = ptr;
			}
		}
		else if (pow(connected1Dis,2) == pow(connected2Dis,2) && connected1Dis > distance)
		{
			leftMost = LeftMost(connected2, connected1);
			if (leftMost->myId == connected1->myId)
			{
				connected2 = ptr;
				connected2Dis = distance;
			}
			else
			{
				connected1 = ptr;
				connected1Dis = distance;
			}
		}
		else if ( pow(connected1Dis,2) == pow(connected2Dis,2) && pow(connected1Dis,2) == pow(distance,2))
		{
			leftMost = LeftMost(connected1, connected2);
			if (leftMost->myId == connected1->myId)
			{
				rightMost = connected2;
			}
			else
			{
				rightMost = connected1;
			}
			leftMost = LeftMost(rightMost, ptr);
			if (leftMost->myId == ptr->myId && rightMost->myId == connected1->myId)
			{
				connected1 = ptr;
				connected1Dis = distance;
			}
			else if (leftMost->myId == ptr->myId && rightMost->myId == connected2->myId)
			{
				connected2 = ptr;
				connected2Dis = distance;
			}
		}
	}
};
//pre: key must contain the same unique points as are in the matrix
//matrix is an adjency list of all stations being examined
//post: will look at the frist point in the matrix and add it and what it's connected to, 
//to a list then what those connected points are connected to and add them to the list so on and so fourth
// untill all points in list have be examined then if that list is equal to then all points are connected and will return true
//otherwise will return false
bool AllPointsContected(Matrix<int> matrix, vector<int> key)
{
	
	vector<int> currentPoints;
	vector<int> keyTemp(key);
	sort(keyTemp.begin(), keyTemp.end());
	int currentPoint;
	currentPoints.push_back(matrix[0][0]);
	for (int i = 0; i < currentPoints.size(); i++)
	{
		currentPoint = find(matrix[0].begin(), matrix[0].end(), currentPoints[i]) -  matrix[0].begin();
		if (matrix[1][currentPoint] > -1 && find(currentPoints.begin(), currentPoints.end(), matrix[1][currentPoint]) == currentPoints.end())
		{
			currentPoints.push_back(matrix[1][currentPoint]);
		}
		if (matrix[2][currentPoint] > -1 && find(currentPoints.begin(), currentPoints.end(), matrix[2][currentPoint]) == currentPoints.end())
		{
			currentPoints.push_back(matrix[2][currentPoint]);
		}
	}

	sort(currentPoints.begin(), currentPoints.end());
	if (currentPoints == keyTemp)
	{
		return true;
	}
	return false;
}
class temp
{
public:
	int id;
	temp(int id)
	{
		this->id = id;
	}
};



int main()
{
	
	struct LessThan {
		bool operator()(temp & rhs, temp & lhs) 
		{
			return rhs.id > lhs.id;
		}
	};

	priority_queue<temp, vector<temp>, LessThan> test;
	temp test2(1);
	temp test3(3);
	temp test4(-2);
	test.push(test2);
	test.push(test3);
	test.push(test4);
	temp answer = test.top();
	cout << answer.id << endl;
	/*vector<int> key;
	vector<Station *> stations;
	Station * tempStation;
	int numStations;
	double tempx;
	double tempy;
	cin >> numStations;
	while (numStations != 0)
	{
		Matrix<int> adjList(3, numStations);
		for (int i = 0; i < numStations; i++)
		{
			key.push_back(i);
			cin >> tempx;
			cin >> tempy;
			tempStation = new Station(i, tempx, tempy);
			stations.push_back(tempStation);
		}
		for (Station * x : stations)
		{
			for (Station * y : stations)
			{
				if (x->GetId() != y->GetId())
				{
					x->CalulateNeighbor(y);
				}
			}
		}
		for (int i = 0; i < numStations; i++)
		{
			adjList[0][i] = stations[i]->GetId();
			adjList[1][i] = stations[i]->GetConnected1ID();
			adjList[2][i] = stations[i]->GetConnected2ID();
		}
		if (AllPointsContected(adjList, key))
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
		stations.clear();
		key.clear();
		cin >> numStations;
	}*/
	system("pause");
	return 0;
}