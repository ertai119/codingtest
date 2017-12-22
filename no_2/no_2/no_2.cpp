// no_2.cpp : Defines the entry point for the console application.
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
#include <thread>
#include <future>

using namespace std;

int main() {

	unsigned long long a = 85;
    unsigned long long b = 97;
    unsigned long long t = 1234567891234567890;
	
	/*
	unsigned long long a = 2;
	unsigned long long b = 3;
	unsigned long long t = 20;
	*/

	unsigned long long divideValue = (unsigned long long)pow(10, 9) + 7;

	unsigned long long exp = t;
	unsigned long long result = 1;
	unsigned long long x = (b) % divideValue;
	while (exp > 0)
	{
		if (exp % 2 == 1)
		{
			result = (result * x) % divideValue;
		}
		x = (x * x) % divideValue;
		exp = exp / 2;
	}

	result = (result * a) % divideValue;
	std::cout << result;

	return 0;
}