// DirectShow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <random>

class CObj : public std::enable_shared_from_this < CObj >
{
	friend class CObjMgr;
protected:
	CObj(){ std::cout << "Create CObj" << std::endl; }
	~CObj() {std::cout << "Destory CObj" << std::endl; }
};


class  CObjMgr
{
public:
	class deleter
	{
	public:
		void operator()(CObj* p)
		{
			delete p;
		}
	};

	std::shared_ptr<CObj> create(){
		m_ptr = new CObj();
		return std::shared_ptr<CObj>(m_ptr, deleter());
	}
public:
	CObj* m_ptr;
};

int SafeDivide(int num, int den)
{
	if (den == 0)
		throw std::invalid_argument("Divide by zero");
	return num / den;
}

#include <sstream>

int _tmain(int argc, _TCHAR* argv[])
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> dis(0,34);
	std::uniform_int_distribution<int> one(0,17);
	for(int i=0;i<6;i++)  
	{  
		std::cout<<dis(generator) << " " ;  
	} 

	std::cout<< one(generator) << std::endl; 

	std::cout<< "OK";
#if 0
	std::ifstream inFile("input.txt");
	std::ofstream outFile("output.txt");

	inFile.tie(&outFile);

	outFile << "Hello there !" << std::endl;
	
	std::string strNextTokens;

	inFile >> strNextTokens;

	std::cout << strNextTokens << std::endl;



	std::ofstream fout("test.out");
	if (!fout)
		return 0;

	fout << "12345";
	std::ios_base::streampos curstreampos = fout.tellp();
	if (5 == curstreampos)
		std::cout << "Test passed: Currently at position 5" << std::endl;

	fout.seekp(2, std::ios_base::beg);
	fout << 0;
	fout.close();

	std::ifstream fin("test.out");
	if (!fin)
		return 0;

	int testVal;
	fin >> testVal;
	const int expected = 12045;
	if (testVal == expected)
		std::cout << "Test passed: value is: " << expected << std::endl;

	std::cout << "Enter tokens.Control + z(windows) to end" << std::endl;
	std::ostringstream outStream;

	while (std::cin)
	{
		std::string strNextToken;
		std::cin >> strNextToken;

		if (strNextToken == "Done")
			break;
		outStream << strNextToken << "\t";
	}

	std::cout << "The end result is:" << outStream.str() << std::endl;


	std::string strFloat = std::to_string(1.0f);
	std::string strDouble = std::to_string(2.0);
	try{
		std::cout << SafeDivide(5, 2) << std::endl;
		std::cout << SafeDivide(10, 0) << std::endl;
		std::cout << SafeDivide(3, 3) << std::endl; 
	}
	catch(const std::invalid_argument& e){
		std::cout << "Caught exception:" << e.what() << std::endl;
	}

	

	CObjMgr* pMgr = new CObjMgr();

	std::shared_ptr<CObj> pObj1 = pMgr->create();
	std::cout << "���ü���" << pObj1.use_count() << std::endl;
	std::shared_ptr<CObj> pObj2 = pMgr->m_ptr->shared_from_this();
	std::cout << "���ü���" << pObj1.use_count() << std::endl;

	pObj1.reset();
	std::cout << "���ü���" << pObj1.use_count() << std::endl;
	std::cout << "���ü���" << pObj2.use_count() << std::endl;
	pObj2.reset();
	std::cout << "���ü���" << pObj1.use_count() << std::endl;
	std::cout << "���ü���" << pObj2.use_count() << std::endl;

	try
	{

	}
	catch (...)
	{

	}


    HRESULT hr = CoInitialize(NULL);
    IGraphBuilder *pGraph;
    
    hr = CoCreateInstance(CLSID_FilterGraph,NULL, CLSCTX_INPROC_SERVER,IID_IGraphBuilder, (void **)&pGraph);
    if (FAILED(hr))
    {

    }


    IMediaControl *pControl;
    IMediaEvent   *pEvent;
    IMediaEventEx *pEventEx;
    
    hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
    hr = pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pEventEx);


    hr = pGraph->RenderFile(L"C:\\Example.avi", NULL);

    hr = pControl->Run();

    long evCode = 0;
    pEvent->WaitForCompletion(INFINITE, &evCode);
    pControl->Release();
    pEvent->Release();
    pGraph->Release();
    CoUninitialize();

#endif
	return 0;
}

