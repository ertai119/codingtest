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

using namespace std;
int main() {
	
	int a = 85;
	int b = 97;
	unsigned long long t = 1234567891234567890;
	unsigned long long limitC = pow(10, 19);
	/*
	for(;;)
	{
		std::cin >> a;
		std::cin >> b;
		std::cin >> t;
		if (a <= 0 || a > 100)
		{
			continue;
		}

		if (b <= 0 || b > 100)
		{
			continue;
		}
		
		if (t <= 0 || t > limitC)
		{
			continue;
		}

		break;
	}*/

	unsigned long long divide = pow(10, 9) + 7;
	unsigned long long resultA_ = pow(b, t);
	unsigned long long resultA = a * resultA_;
	unsigned long long resultDivide = (unsigned long long)(resultA / divide);
	unsigned long long temp = resultDivide * divide;
	unsigned long long result = resultA - temp;
	std::cout << result;
	
	return 0;
}