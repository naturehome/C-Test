// CurlTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::string> vec = { "hello", " ", "world" };
	std::string s = std::accumulate(vec.begin(), vec.end(), s);
	std::cout << s << std::endl;

	return 0;
}

