#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<pair<int, int>, int>> wEdges;

bool dirCycleDetect(int src, vector<int> &num, vector<vector<int>> Adj_list)
{
	num[src]++;
	for (int i = 0; i < Adj_list[src].size(); i++)
	{
		if (num[Adj_list[src][i]] == 0)
		{
			if (dirCycleDetect(Adj_list[src][i], num, Adj_list))
				return true;
		}
		else if (num[Adj_list[src][i]] != 9999)
		{
			return true;
		}
	}
	num[src] = 9999;
	return false;
}

bool isdirCycleDetect(int size, vector<vector<int>> Adj_list)
{
	vector <int> num(size, 0);
	for (int u = 0; u < size; u++)
	{
		if (num[u] == 0)
		{
			if (dirCycleDetect(u, num, Adj_list))
				return true;
		}
	}
	return false;
}

bool unDircycleDetectK(int src, vector<bool> &visit, int parent, vector<vector<int>> Adj_list)
{
	visit[src] = true;

	for (int i = 0; i < Adj_list[src].size(); i++)
	{
		if (!visit[Adj_list[src][i]])
		{
			if (unDircycleDetectK(Adj_list[src][i], visit, src, Adj_list))
				return true;
		}
		else if (Adj_list[src][i] != parent)
		{
			return true;
		}
	}
	return false;
}

bool isunDIrcycleK(int size, vector<vector<int>> Adj_list)
{
	vector <bool> visit(size, false);
	for (int u = 0; u < size; u++)
	{
		if (!visit[u])
		{
			if (unDircycleDetectK(u, visit, -1, Adj_list))
				return true;
		}
	}
	return false;
}

void sortWEdges(vector<pair<pair<int, int>, int>> &wEdges)
{
	for (size_t i = 1; i < wEdges.size(); i++)
	{
		vector<pair<pair<int, int>, int>> key;
		key.push_back(wEdges[i]);
		int j = i - 1;

		while (j >= 0 && wEdges[j].second > key[0].second)
		{
			wEdges[j + 1] = wEdges[j];
			--j;
		}
		wEdges[j + 1] = key[0];
	}
}

void krushMinSpanTree(vector<pair<pair<int, int>, int>> wEdges, int numvertices)
{
	vector<pair<pair<int, int>, int>> mst;
	sortWEdges(wEdges);

	for (size_t i = 0; i < wEdges.size(); i++)
	{
		cout << wEdges[i].first.first << "--" << wEdges[i].first.second << "=" << wEdges[i].second << endl;
	}
	mst.push_back(wEdges[0]);

	for (size_t i = 1; i < wEdges.size() && mst.size() < numvertices - 1; i++)
	{
		vector<vector<int>> Adj_list(numvertices);

		//for (size_t j = 0; j < mst.size(); j++)
		//{
		//	Adj_list[mst[j].first.first].push_back(mst[j].first.second);
		//}
		//Adj_list[wEdges[i].first.first].push_back(wEdges[i].first.second);

		//if (!isdirCycleDetect(numvertices, Adj_list))
		//{
		//	mst.push_back(wEdges[i]);
		//}

		for (size_t j = 0; j < mst.size(); j++)
		{
			Adj_list[mst[j].first.first].push_back(mst[j].first.second);
			Adj_list[mst[j].first.second].push_back(mst[j].first.first);
		}
		Adj_list[wEdges[i].first.first].push_back(wEdges[i].first.second);
		Adj_list[wEdges[i].first.second].push_back(wEdges[i].first.first);

		if (!isunDIrcycleK(numvertices, Adj_list))
		{
			mst.push_back(wEdges[i]);
		}



	}
	cout << "MST:" << endl;
	for (size_t i = 0; i < mst.size(); i++)
	{
		cout << mst[i].first.first << "--" << mst[i].first.second << "=" << mst[i].second << endl;
	}
}

int main()
{
	wEdges.push_back(make_pair(make_pair(0, 1), 6));
	wEdges.push_back(make_pair(make_pair(0, 2), 5));

	wEdges.push_back(make_pair(make_pair(1, 2), 9));
	wEdges.push_back(make_pair(make_pair(1, 4), 13));

	wEdges.push_back(make_pair(make_pair(2, 3), 16));
	wEdges.push_back(make_pair(make_pair(2, 5), 12));

	wEdges.push_back(make_pair(make_pair(3, 4), 15));
	wEdges.push_back(make_pair(make_pair(3, 5), 7));

	wEdges.push_back(make_pair(make_pair(4, 6), 8));

	wEdges.push_back(make_pair(make_pair(5, 6), 3));

	krushMinSpanTree(wEdges, 7);
	return 0;
}
