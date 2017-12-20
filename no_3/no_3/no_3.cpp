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

enum class eDIR {
    INVALID = 0,
    EAST,
	SOUTH, 
    WEST,
	NORTH,
};

using Position = std::pair<int, int>;

constexpr Position INVALID_POSITION = { -1, -1 };
constexpr Position EAST_DIR = {1, 0};
constexpr Position WEST_DIR = {-1, 0};
constexpr Position NORTH_DIR = {0, -1};
constexpr Position SOUTH_DIR = {0, 1};
const std::vector<Position> DIRS = {EAST_DIR, WEST_DIR, NORTH_DIR, SOUTH_DIR};

enum class eMOVE
{
	INVALID = 0,
	FORWARD,
	LEFT,
	RIGHT,
};

const char* GetMoveStr(eMOVE mode)
{
	switch (mode)
	{
	case eMOVE::INVALID:
		return " ";
	case eMOVE::FORWARD:
		return "F";
	case eMOVE::LEFT:
		return "L";
	case eMOVE::RIGHT:
		return "R";
	default:
		break;
	}

	return "X";
}

struct Node
{
	Position pos = INVALID_POSITION;
	bool obstacle = false;
    eDIR eDir = eDIR::INVALID;
	Position parentPos = INVALID_POSITION;
	float weight = 0.f;
	std::vector<eMOVE> moveCmd;

	bool operator<(const Node& rhs) const {
		return weight > rhs.weight;
	}
};

eDIR GetDirByStr(const string& str)
{
    if (str.compare("EAST") == 0)
    {
        return eDIR::EAST;
    }
    else if (str.compare("WEST") == 0)
    {
        return eDIR::WEST;
    }
    else if (str.compare("NORTH") == 0)
    {
        return eDIR::NORTH;
    }
    else if (str.compare("SOUTH") == 0)
    {
        return eDIR::SOUTH;
    }

    return eDIR::INVALID;
}

eDIR GetDirByPosition(const Position& pos)
{
	if (pos == EAST_DIR)
		return eDIR::EAST;
	else if (pos == WEST_DIR)
		return eDIR::WEST;
	else if (pos == NORTH_DIR)
		return eDIR::NORTH;
	else if (pos == SOUTH_DIR)
		return eDIR::SOUTH;

	return eDIR::INVALID;
}

float CalcDistanceWeight(const Node& neighborNode, const Node& goal)
{
	return static_cast<float>(sqrt(pow(goal.pos.first - neighborNode.pos.first, 2)
		+ pow(goal.pos.second - neighborNode.pos.second, 2)));
}

float CalcWeight(const Node& targetNode, Node& neighborNode, const Position& neighborDir)
{
	eDIR eNeighboDir = GetDirByPosition(neighborDir);
	
	const float WEIGHT_FORWARD = 2.f;

	if (targetNode.eDir == eNeighboDir)
	{
		neighborNode.moveCmd.push_back(eMOVE::FORWARD);
		return WEIGHT_FORWARD;
	}

	float rotateWeight = 0;
	int rotateDelta = static_cast<int>(eNeighboDir) - static_cast<int>(targetNode.eDir);
	if (rotateDelta < 0)
	{
		int convertDelta = -1 * rotateDelta;
		rotateWeight = convertDelta + WEIGHT_FORWARD;
		for (int i = 0; i < convertDelta; i++)
		{
			neighborNode.moveCmd.push_back(eMOVE::RIGHT);
		}		
		neighborNode.moveCmd.push_back(eMOVE::FORWARD);
	}
	else
	{
		rotateWeight = rotateDelta + WEIGHT_FORWARD;
		for (int i = 0; i < rotateDelta; i++)
		{
			neighborNode.moveCmd.push_back(eMOVE::LEFT);
		}
		neighborNode.moveCmd.push_back(eMOVE::FORWARD);
	}
	
	return rotateWeight;
}

bool SearchAround(Node& goal,
    std::priority_queue<Node>& openList,
    std::set<Position>& closeList,
    std::map<Position, Node>& mapData)
{
	if (openList.empty())
		return false;

	Node targetNode = openList.top();
	openList.pop();

	closeList.insert(targetNode.pos);

	for (const auto& dir : DIRS)
	{
		Position pos = Position(targetNode.pos.first + dir.first, targetNode.pos.second + dir.second);
		auto it = closeList.find(pos);
		if (it != closeList.end())
		{
			continue;
		}

		auto mapIt = mapData.find(pos);
		if (mapIt == mapData.end())
		{
			continue;
		}

		Node& neighborNode = mapIt->second;
		if (neighborNode.obstacle == true)
		{
			closeList.insert(neighborNode.pos);
			continue;
		}

		neighborNode.weight = CalcWeight(targetNode, neighborNode, dir);
		neighborNode.weight += CalcDistanceWeight(neighborNode, goal);
		neighborNode.parentPos = targetNode.pos;
		neighborNode.eDir = GetDirByPosition(dir);

		openList.push(neighborNode);

		if (neighborNode.pos == goal.pos)
		{
			goal.parentPos = targetNode.pos;
			return true;
		}
	}    

	return SearchAround(goal, openList, closeList, mapData);
}

void MakePath(const Node& node, const std::map<Position, Node>& mapData, std::list<Position>& path)
{
	auto it = mapData.find(node.parentPos);
	if (it != mapData.end())
	{
		path.push_front(node.parentPos);
		MakePath(it->second, mapData, path);
	}
}

string Solve(string D, int W, std::vector<string> MAP)
{
	std::map<Position, Node> mapData;
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
                node.eDir = GetDirByStr(D);
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

    std::priority_queue<Node, std::vector<Node>> openList;
	openList.push(player);

    std::set<Position> closeList;

	std::list<Position> path;
    bool find = SearchAround(goal, openList, closeList, mapData);
	if (find)
	{
		MakePath(goal, mapData, path);
	}

	std::string outPathStr;
	for (const auto& pos : path)
	{
		auto it = mapData.find(pos);
		if (it == mapData.end())
			continue;

		for (const auto& cmd : it->second.moveCmd)
		{
			outPathStr.append(GetMoveStr(cmd));
		}
	}

	//FFLFFRFFRFLFFFLFFFLFFFFFRFFFRFFFF
	return outPathStr;
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

