#include "stdafx.h"
#include <string>
const int MAX_DISPATCH_ITEM = 256;

typedef int(*ProcessFuncPtr)(void* para_in, void* para_out);

typedef struct tagDispatchItem {
    unsigned int    func_no;
    ProcessFuncPtr  func_ptr;
}DISPATCH_ITEM;

DISPATCH_ITEM dispatch_table[MAX_DISPATCH_ITEM] = {};


int ProcessControl(unsigned int func_no, void* para_in, void* para_out)
{
    for (size_t i = 0; i < MAX_DISPATCH_ITEM; i++)
    {
        if (dispatch_table[i].func_no == func_no) {
            return dispatch_table[i].func_ptr(para_in, para_out);
        }
    }
    return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
    std::wstring strtest = L"21231312313138&fsfsfsd";

    std::wstring::size_type iPos = strtest.find(_T('&'));
    if (iPos != std::wstring::npos)
    {
        std::wstring test1 = strtest.substr(iPos + 1).c_str();
        strtest = strtest.substr(0, iPos);
    }

    return 0;
}
