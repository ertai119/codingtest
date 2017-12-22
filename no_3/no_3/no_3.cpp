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
	NORTH,
    WEST,
	SOUTH,
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

class PathGenerator
{
public:

	struct Node
	{
		Position pos = INVALID_POSITION;
		bool obstacle = false;
		eDIR eDir = eDIR::INVALID;
		Position parentPos = INVALID_POSITION;
		float distWeight = 0.f;
		float rotateWeight = 0.f;
		std::vector<eMOVE> moveCmd;

		bool operator<(const Node& rhs) const {
			return distWeight + rotateWeight > rhs.distWeight + rhs.rotateWeight;
		}
	};

	bool MakeMap(string D, int W, std::vector<string> MAP);
	bool Generator();
	void MakeResult(std::string& pathStr);

private:

	std::map<Position, Node> _mapData;
    std::map<Position, Node> _openList;
	std::set<Position> _closeList;
	Node _player;
	Node _goal;

	float CalcDistanceWeight(const Node& neighborNode, const Node& goal) const;
	float CalcRotateWeight(const Node& targetNode, Node& neighborNode, const Position& neighborDir) const;
	bool SearchAround(Node& goal,
        std::map<Position, Node>& openList,
		std::set<Position>& closeList,
		std::map<Position, Node>& mapData);
	void RecordPath(const Node& node, std::list<Node>& record) const;
};

float PathGenerator::CalcDistanceWeight(const Node& neighborNode, const Node& goal) const
{
	return static_cast<float>(sqrt(pow(goal.pos.first - neighborNode.pos.first, 2)
		+ pow(goal.pos.second - neighborNode.pos.second, 2)));
}

float PathGenerator::CalcRotateWeight(const Node& targetNode, Node& neighborNode, const Position& neighborDir) const
{
	eDIR eNeighboDir = GetDirByPosition(neighborDir);

	const float WEIGHT_FORWARD = 2.f;
	const float WEIGHT_ROTATE = 1.f;

	if (targetNode.eDir == eNeighboDir)
	{
		return WEIGHT_FORWARD;
	}

	float rotateWeight = 0;
	int rotateDelta = static_cast<int>(eNeighboDir) - static_cast<int>(targetNode.eDir);
	if (rotateDelta < 0)
	{
		rotateDelta = -1 * rotateDelta;
	}

	if (rotateDelta % 2 == 1)
		rotateWeight = WEIGHT_ROTATE;
	else
		rotateWeight = 2 * WEIGHT_ROTATE;

	return rotateWeight + WEIGHT_FORWARD;
}

bool PathGenerator::SearchAround(Node& goal
	, std::map<Position, Node>& openList
	, std::set<Position>& closeList
	, std::map<Position, Node>& mapData)
{
	if (openList.empty())
		return false;

	Node targetNode = openList.begin()->second;
    openList.erase(openList.begin());

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

        auto openIt = openList.find(neighborNode.pos);
        if (openIt != openList.end())
        {
            continue;
        }

        float distWeight = CalcDistanceWeight(neighborNode, goal);
        float rotateWeight = CalcRotateWeight(targetNode, neighborNode, dir);
		float calcRotateWieght = neighborNode.rotateWeight + rotateWeight + targetNode.rotateWeight;

		neighborNode.distWeight = distWeight;
        neighborNode.rotateWeight = calcRotateWieght;
        neighborNode.parentPos = targetNode.pos;
        neighborNode.eDir = GetDirByPosition(dir);

        openList.insert({neighborNode.pos, neighborNode});

		if (neighborNode.pos == goal.pos)
		{
			goal.parentPos = targetNode.pos;
			goal.eDir = GetDirByPosition(dir);
			return true;
		}
	}

	return SearchAround(goal, openList, closeList, mapData);
}

bool PathGenerator::Generator()
{
	_openList = std::map<Position, Node>();
    _openList.insert({_player.pos, _player});

	_closeList.clear();

	bool find = SearchAround(_goal, _openList, _closeList, _mapData);
	return find;
}

bool PathGenerator::MakeMap(string D, int W, std::vector<string> MAP)
{
	_mapData.clear();
	_player = Node();
	_goal = Node();

	for (size_t y = 0; y < MAP.size(); y++)
	{
		const string& str = MAP[y];
		for (size_t x = 0; x < str.size(); x++)
		{
			string ch;
			char temp = str.at(x);
			ch = temp;
			Node node;
			node.pos = { static_cast<int>(x), static_cast<int>(y) };

			if (ch.compare("T") == 0)
			{
				node.eDir = GetDirByStr(D);
				_player = node;
			}
			else if (ch.compare("#") == 0)
			{
				node.obstacle = true;
			}
			else if (ch.compare("G") == 0)
			{
				_goal = node;
			}

			_mapData.insert({ {static_cast<int>(x), static_cast<int>(y)}, node });
		}
	}

	return !_mapData.empty();
}

void PathGenerator::RecordPath(const Node& node, std::list<Node>& record) const
{
	auto it = _mapData.find(node.parentPos);
	if (it != _mapData.end())
	{
		record.push_front(node);
		RecordPath(it->second, record);
	}
}

void PathGenerator::MakeResult(std::string& pathStr)
{
	std::list<Node> record;
	RecordPath(_goal, record);

	Node targetNode = _player;
	for (const auto& node : record)
	{
		if (targetNode.eDir == node.eDir)
		{
			pathStr.append(GetMoveStr(eMOVE::FORWARD));
		}
		else
		{
			int convertedDir = static_cast<int>(node.eDir);
			if (targetNode.eDir == eDIR::SOUTH && node.eDir == eDIR::EAST)
				convertedDir += static_cast<int>(eDIR::SOUTH);

			if (targetNode.eDir == eDIR::EAST && node.eDir == eDIR::SOUTH)
				convertedDir -= static_cast<int>(eDIR::SOUTH);

			int delta = convertedDir - static_cast<int>(targetNode.eDir);
			if (delta > 0)
			{
				pathStr.append(GetMoveStr(eMOVE::LEFT));
				pathStr.append(GetMoveStr(eMOVE::FORWARD));
			}
			else
			{
				pathStr.append(GetMoveStr(eMOVE::RIGHT));
				pathStr.append(GetMoveStr(eMOVE::FORWARD));
			}
		}
		targetNode = node;
	}

	return;
}

string Solve(string D, int W, std::vector<string> MAP)
{
	PathGenerator pathGen;

	bool load = pathGen.MakeMap(D, W, MAP);
	bool find = false;

	if (load)
		find = pathGen.Generator();

	string pathStr;
	if (find)
		pathGen.MakeResult(pathStr);

	return pathStr;
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

