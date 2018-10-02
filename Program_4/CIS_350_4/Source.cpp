#include <iostream>
#include <vector>
#include <queue>
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
class PokeStop
{
	public:
	int GetLowerBound()
	{
		return lowerBound;
	}
	int GetCurrentDistance()
	{
		return currentDistance;
	}
	void CalulateCurrentDistance(const Matrix<int> & matrix)
	{
		int disTemp = 0;
		for (int i = 0; i < visitiedLocations.size() - 1; i++)
		{

		}
		
	}
	void AddNextLocation(int temp)
	{
		visitiedLocations.push_back(temp);
	}
	vector<int> GetVistitedLocations()
	{
		return visitiedLocations;
	}
	void AddCurrentPoke(string temp)
	{
		currentPoke.push_back(temp);
	}
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

class Compare
{
	bool operator()(PokeStop lhs, PokeStop rhs)
	{
		return lhs.GetLowerBound() > rhs.GetLowerBound();
	}
};
int main()
{
	return 0;
}