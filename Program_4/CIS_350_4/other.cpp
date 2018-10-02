//
//vector<string> duphelper;
//for (int i = 0; i < currentPoke.size() - 1; i++)
//{
//	duphelper.push_back(currentPoke[i]);
//}
//int tempbound = 0;
//int temp = INT_MAX;
//if (find(duphelper.begin(), duphelper.end(), key[visitiedLocations.back() + 1]) == duphelper.end() && currentPoke.size() > 1)
//{
//	for (int i = 0; i < matrix.numcols(); i++)
//	{
//		if (temp > matrix[visitiedLocations.back()][i] && find(duphelper.begin(), duphelper.end(), key[i + 1]) == duphelper.end() && matrix[visitiedLocations.back()][i] != -1 && find(currentPoke.begin(), currentPoke.end(), key[i + 1]) == currentPoke.end())
//		{
//			temp = matrix[visitiedLocations.back()][i];
//			duphelper.push_back(key[i + 1]);
//		}
//	}
//	if (temp != INT_MAX)
//		tempbound += temp;
//}
//for (int i = 0; i < matrix.numcols(); i++)
//{
//	temp = INT_MAX;
//
//	if (find(visitiedLocations.begin(), visitiedLocations.end() - 1, i) != visitiedLocations.end() - 1)
//	{
//		temp = matrix[visitiedLocations.at(i)][visitiedLocations.at(i + 1)];
//	}
//	else
//	{
//		for (int j = 0; j < matrix[i].size(); j++)
//		{
//			if (temp > matrix[i][j] && find(duphelper.begin(), duphelper.end(), key[j + 1]) == duphelper.end() && matrix[i][j] != -1 && find(currentPoke.begin(), currentPoke.end(), key[j + 1]) == currentPoke.end())
//			{
//				temp = matrix[i][j];
//				duphelper.push_back(key[j + 1]);
//			}
//		}
//	}
//	if (temp != INT_MAX)
//	{
//		tempbound += temp;
//	}
//}
//lowerBound = tempbound;
//	}
//	void AddNextLocation(PokeStop stop, priority_queue<PokeStop> & queue, Matrix<int> matrix, vector<string> key)
//	{
//		PokeStop temp(stop);
//		for (int i = 0; i < matrix.numcols(); i++)
//		{
//			if (find(temp.currentPoke.begin(), temp.currentPoke.end(), key[i + 1]) == currentPoke.end())
//			{
//				temp.visitiedLocations.push_back(i);
//				temp.currentPoke.push_back(key[i + 1]);
//				temp.CalulateLowerBound(matrix, key);
//				temp.CalulateCurrentDistance(matrix);
//				queue.push(temp);
//			}
//		}