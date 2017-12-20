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

enum eDIR {
    INVALID = 0,
    EAST,
    SOUTH,
    WEST,
    NORTH,
};

constexpr std::pair<int, int> EAST_DIR = {1, 0};
constexpr std::pair<int, int> WEST_DIR = {-1, 0};
constexpr std::pair<int, int> SOUTH_DIR = {0, -1};
constexpr std::pair<int, int> NORTH_DIR = {0, 1};
const std::vector<pair<int, int>> DIRS = {EAST_DIR, WEST_DIR, SOUTH_DIR, NORTH_DIR};

struct Node
{
    std::pair<int, int> pos = {-1, -1};
	bool obstacle = false;
    eDIR eDir = INVALID;
};

eDIR GetDirFromStr(const string& str)
{
    if (str.compare("EAST") == 0)
    {
        return EAST;
    }
    else if (str.compare("WEST") == 0)
    {
        return WEST;
    }
    else if (str.compare("SOUTH") == 0)
    {
        return SOUTH;
    }
    else if (str.compare("NORTH") == 0)
    {
        return NORTH;
    }

    return INVALID;
}

void SearchAround(const Node& goal,
    std::queue<std::pair<int, int>>& openList,
    std::queue<std::pair<int, int>>& closeList,
    const std::map<std::pair<int, int>, Node>& mapData)
{
    const std::pair<int, int>& targetNode = openList.front();
    openList.pop();

    closeList.push(targetNode);
}

int CalcWeight()
{
    return 0;
}

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
            string ch;
            char temp = str.at(x);
            ch = temp;
			Node node;
            node.pos = {static_cast<int>(x), static_cast<int>(y)};

			if (ch.compare("T") == 0)
			{
                node.eDir = GetDirFromStr(D);
				player = node;
			}
			else if (ch.compare("#") == 0)
			{
				node.obstacle = true;
			}
			else if (ch.compare("G") == 0)
			{
				goal = node;
			}

			mapData.insert({ { x, y }, node });
		}
	}

    std::queue<std::pair<int, int>> openList;
    openList.push(player.pos);

    std::queue<std::pair<int, int>> closeList;

    SearchAround(goal, openList, closeList, mapData);

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

