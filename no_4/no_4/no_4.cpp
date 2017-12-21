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

	std::vector< std::pair<int, int> > shootHistory;
	cin >> shootingCount;
	for (int i = 0; i < shootingCount; i++)
	{
		int from;
		int to;
		cin >> from;
		cin >> to;
		shootHistory.push_back({ from, to});
	}

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

    return 0;
}


