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
	std::vector<unsigned long long> inputDatas;

	cin >> dataCount;
	for (int i = 0; i < dataCount; i++)
	{
		unsigned long long input = 0;
		cin >> input;
		inputDatas.push_back(input);
	}

	std::vector<unsigned long long> allBits;
	for (const auto& input : inputDatas)
	{
		unsigned long long value = 1;
		for (int i = 0; i < 64; i++)
		{
			value = value << 1;
			if (input <= value)
			{
				allBits.push_back(value);
				break;
			}
		}
	}

	unsigned long long result = allBits[0];
	for (int i = 1; i < allBits.size(); i++)
	{
		result = result ^ allBits[i];
	}

	cout << result << endl;
	return 0;
}
