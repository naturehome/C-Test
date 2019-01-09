// stringTestDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "stringTestDll.h"


// This is an example of an exported variable
STRINGTESTDLL_API int nstringTestDll=0;

// This is an example of an exported function.
STRINGTESTDLL_API int fnstringTestDll(void)
{
	return 42;
}

STRINGTESTDLL_API void GetInfo(std::string& str)
{
	str = "abcdefghijklmn";
}

STRINGTESTDLL_API std::string GetInfo2()
{
	return "abcdefghijklmn";
}
// This is the constructor of a class that has been exported.
// see stringTestDll.h for the class definition
CstringTestDll::CstringTestDll()
{
	return;
}
