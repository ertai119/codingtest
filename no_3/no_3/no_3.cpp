// no_3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Node
{
	int x = 0;
	int y = 0;
	bool obstacle = false;
};

string Solve(string D, int W, std::vector<string> MAP)
{
	std::map<std::pair<int, int>, Node> mapData;
	Node player;
	Node goal;

	for (size_t y = 0; y < MAP.size() ; y++)
	{
		const string& str = MAP[y];
		for (size_t x = 0; x < str.size(); x++)
		{
			const char* ch = &(str.at(0));
			Node node;
			node.x = x;
			node.y = y;

			if (strcmp(ch, "T") == 0)
			{
				player = node;
			}
			else if (strcmp(ch, "#") == 0)
			{
				node.obstacle = true;
			}
			else if (strcmp(ch, "G") == 0)
			{
				goal = node;
			}

			mapData.insert({ { x,y }, node });
		}
	}

	return "";
}

int main()
{
	ifstream in("input001.txt");

	string dir;
	int width;
	int height;
	std::vector<std::string> map;

	if (in.is_open()) {

		getline(in, dir);
		in >> width;
		in >> height;

		string s;
		while (!in.eof())
		{
			getline(in, s);
			if (s.empty())
				continue;

			map.push_back(s);
		}

		in.close();

		Solve(dir, width, map);
	}

    return 0;
}

