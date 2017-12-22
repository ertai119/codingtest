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

unsigned long long DivideValue(unsigned long long left, unsigned long long value, int step)
{
    unsigned long long left2 = left / 2;
    unsigned long long right2 = left2 + left % 2;
    
    step++;
    if (step >= 30 || left < 1000)
    {
		unsigned long long retValue = (unsigned long long)pow(value, left);
        return retValue;
    }

    unsigned long long leftRet = DivideValue(left2, value, step);
    unsigned long long rightRet = DivideValue(right2, value, step);

    return leftRet * rightRet;
}

int main() {


	unsigned long long a = 85;
    unsigned long long b = 97;
    unsigned long long t = 1234567891234567890;
	/*
	std::cin >> a;
	std::cin >> b;
	std::cin >> t;
	*/
    unsigned long long left = t / 2;
    unsigned long long right = left + t % 2;
    
    int step = 0;
    unsigned long long value1 = DivideValue(left, b, step);
    unsigned long long value2 = DivideValue(right, b, step);

    unsigned long long totalValue = value1 * value2;

	unsigned long long divideValue = (unsigned long long)pow(10, 9) + 7;
	unsigned long long tempResult = a * totalValue;
	unsigned long long divide = (unsigned long long)(tempResult / divideValue);
	unsigned long long tempValue = divide * divideValue;
	unsigned long long result = tempResult - tempValue;

	std::cout << result;

	return 0;
}