// test2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
    int* a = new int(2);
    std::shared_ptr<int> sp1(&a[0]);
    std::shared_ptr<int> sp2(&a[1]);

    std::cout << "the address of a[0] = " << a << std::endl;
    std::cout << "the address of a[1] = " << &a[1] << std::endl;

    std::cout << "the address of a[0] shared = " << sp1.get() << std::endl;
    std::cout << "the address of a[1] shared = " << sp2.get() << std::endl;

	return 0;
}

