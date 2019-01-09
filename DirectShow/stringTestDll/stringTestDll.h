// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STRINGTESTDLL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STRINGTESTDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STRINGTESTDLL_EXPORTS
#define STRINGTESTDLL_API __declspec(dllexport)
#else
#define STRINGTESTDLL_API __declspec(dllimport)
#endif
#include <string>
// This class is exported from the stringTestDll.dll
class STRINGTESTDLL_API CstringTestDll {
public:
	CstringTestDll(void);
	// TODO: add your methods here.
};

extern STRINGTESTDLL_API int nstringTestDll;

STRINGTESTDLL_API void GetInfo(std::string& str);
STRINGTESTDLL_API std::string GetInfo2();
STRINGTESTDLL_API int fnstringTestDll(void);
