// no_4.cpp : Defines the entry point for the console application.
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

struct Point {
	float x = 0;
	float y = 0;
	Point() {

	}
	Point(float x_, float y_)
		: x(x_), y(y_)
	{}
};

struct Npc {
	Npc() {

	}

	Npc(Point point, float radius_)
		: pt(point), radius(radius_)
	{

	}
	Point pt;
	float radius = 0.f;
	bool dead = false;
};

float Dot(Point p1, Point p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

int CheckLine(const Point& from, const Point& dir, const Point& circlePt, float radius)
{
	float a, b, c, d;

    Point end = Point(from.x + dir.x, from.y + dir.y);
    Point b1 = Point(from.x - circlePt.x, from.y - circlePt.y);

    a = Dot(dir, dir);
    b = Dot(dir, b1) * 2.0f;
    c = Dot(b1, b1) - (radius * radius);
    d = (b*b) - (4 * a * c);

    int result = 0;
    if (d >= 0.0f)
    {
        float lamba0 = (-b - sqrt(d)) / (2.0f * a);
        if (lamba0 > 0.0f) {
            result = 1;
        }

        float lamba1 = (-b + sqrt(d)) / (2.0f * a);
        if (lamba1 > 0.0f) {
            result = 2;
        }
    }

	return result;
}

int main()
{
	int totalNpc = 0;
	int shootingCount = 0;
	int max_hit_count = 4;

	std::map<int, Npc> npcList;
/*
	cin >> totalNpc;
	for (int i = 0 ; i < totalNpc ; i++)
	{
		int id;
		float x;
		float y;
		float radius;
		cin >> id;
		cin >> x;
		cin >> y;
		cin >> radius;

		Npc npc;
		npc.pt = Point(x, y);
		npc.radius = radius;
		npcList.insert({ id, npc });
	}
	*/
	npcList = {
		{ 0, Npc(Point(12.f, 12.f), 12.f)},
		{ 1, Npc(Point(19.f, 46.f), 19.f)},
		{ 2, Npc(Point(37.f, 10.f), 10.f) },
		{ 3, Npc(Point(49.f, 89.f), 22.f) },
		{ 4, Npc(Point(57.f, 40.f), 17.f) },
		{ 5, Npc(Point(96.f, 42.f), 19.f) },
		{ 6, Npc(Point(132.f, 15.f), 15.f) },
		{ 7, Npc(Point(169.f, 20.f), 20.f) },
		{ 8, Npc(Point(60.f, 10.f), 10.f) },
		{ 9, Npc(Point(168.f, 61.f), 19.f) },
		{ 10, Npc(Point(92.f, 82.f), 19.f) },
		{ 11, Npc(Point(130.f, 55.f), 13.f) },
		{ 12, Npc(Point(130.f, 86.f), 16.f) },
		{ 13, Npc(Point(83.f, 10.f), 10.f) },
		{ 14, Npc(Point(168.f, 102.f), 20.f) },
		{ 15, Npc(Point(87.f, 118.f), 14.f) },
		{ 16, Npc(Point(120.f, 120.f), 16.f) },
		{ 17, Npc(Point(122.f, 156.f), 18.f) },
		{ 18, Npc(Point(10.f, 186.f), 10.f) },
		{ 19, Npc(Point(18.f, 153.f), 18.f) },
		{ 20, Npc(Point(164.f, 160.f), 22.f) },
		{ 21, Npc(Point(59.f, 155.f), 20.f) }
	};

	/*
	npcList = {
		{ 0, Npc(Point(12.f, 12.f), 12.f) },
		{ 1, Npc(Point(50.f, 50.f), 10.f) },
		{ 2, Npc(Point(80.f, 80.f), 10.f) }
	};*/

	std::vector< std::pair<int, int> > shootHistory;
	/*cin >> shootingCount;
	for (int i = 0; i < shootingCount; i++)
	{
		int from;
		int to;
		cin >> from;
		cin >> to;
		shootHistory.push_back({ from, to});
	}
	*/
	shootHistory.push_back({ 1,13 });
	shootHistory.push_back({ 3,4 });
	shootHistory.push_back({ 4,2 });
	shootHistory.push_back({ 6,13 });
	shootHistory.push_back({ 8,3 });
	shootHistory.push_back({ 9,8 });
	shootHistory.push_back({ 11,4 });
	shootHistory.push_back({ 13,6 });
	shootHistory.push_back({ 21,9 });

	//shootHistory.push_back({ 0, 2});

	for (const auto& elem : shootHistory)
	{
		const Npc& fromNpc = npcList[elem.first];
		const Npc& toNpc = npcList[elem.second];

		if (fromNpc.dead == true)
		{
			continue;
		}

		std::map<float, int> hitList;
		for (const auto& pair : npcList)
		{
			if (pair.first == elem.first)
			{
				continue;
			}

			const Npc& targetNpc = pair.second;
			if (targetNpc.dead == true)
			{
				continue;
			}

			float distance = sqrt(pow(targetNpc.pt.x - fromNpc.pt.x, 2) + pow(targetNpc.pt.y - fromNpc.pt.y, 2));
			Point dir((toNpc.pt.x - fromNpc.pt.x) /distance, (toNpc.pt.y - fromNpc.pt.y) / distance) ;

			int checked = CheckLine(fromNpc.pt, dir, targetNpc.pt, targetNpc.radius);
			if (checked >= 2 && distance > 0.f)
			{
				hitList.insert({ distance, pair.first });
			}
		}

		if (hitList.empty() == false)
		{
			int hitCount = 0;
			for (auto it = hitList.cbegin() ; it != hitList.cend(); ++it)
			{
				if (hitCount >= max_hit_count)
				{
					break;
				}

				npcList[it->second].dead = true;
				cout << it->second << endl;
				hitCount++;
			}
		}
	}

	// output
	// 4 13 8 2 0 11 5 15 16 12 9
    return 0;
}


