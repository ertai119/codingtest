// no_1.cpp : Defines the entry point for the console application.
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

int main() {
	
	int dataCount = 0;
	std::vector<int> inputDatas;
	/*
	cin >> dataCount;
	for (int i = 0; i < dataCount; i++)
	{
		int input = 0;
		cin >> input;
		inputDatas.push_back(input);
	}*/

	inputDatas.push_back(3);
	inputDatas.push_back(5);
	inputDatas.push_back(7);

	std::vector<int> outputDatas;
	for (const auto& input : inputDatas)
	{
		int minValue = 0;
		for (int j = 0; j < 32; j++)
		{
			long long npot = 2 << j;
			if (input <= npot)
			{
				minValue = npot;
				break;
			}
		}
		outputDatas.push_back(minValue);
	}
	
	int result = outputDatas[0];
	for (int i = 1 ; i < (int)outputDatas.size(); i++)
	{
		result ^ outputDatas[i];
	}

	cout << result;

	return 0;
}
