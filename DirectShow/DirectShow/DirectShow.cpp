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

std::ostream& operator <<(std::ostream& os, const CObj* obj)
{
	return os << "test";
}

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

void GetResultofPING()
{
	std::string strcmd = "start /b ping 192.168.1.231 > ping.txt";
	system(strcmd.c_str());
	std::fstream inFile;
	try
	{
		inFile.open("ping.txt", std::ios_base::in);
		while (inFile.eof())
		{
			char szInfo[80] = { 0 };
			inFile.getline(szInfo, sizeof(szInfo));
		}
	}
	catch (...)
	{

	}

	
	
	inFile.close();
	system("del ping.txt");
}

HRESULT InitCaptureGraphBuilder(
	IGraphBuilder **ppGraph,  // Receives the pointer.
	ICaptureGraphBuilder2 **ppBuild  // Receives the pointer.
	)
{
	if (!ppGraph || !ppBuild)
	{
		return E_POINTER;
	}
	IGraphBuilder *pGraph = NULL;
	ICaptureGraphBuilder2 *pBuild = NULL;

	// Create the Capture Graph Builder.
	HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL,
		CLSCTX_INPROC_SERVER, IID_ICaptureGraphBuilder2, (void**)&pBuild);
	if (SUCCEEDED(hr))
	{
		// Create the Filter Graph Manager.
		hr = CoCreateInstance(CLSID_FilterGraph, 0, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void**)&pGraph);
		if (SUCCEEDED(hr))
		{
			// Initialize the Capture Graph Builder.
			pBuild->SetFiltergraph(pGraph);

			// Return both interface pointers to the caller.
			*ppBuild = pBuild;
			*ppGraph = pGraph; // The caller must release both interfaces.
			return S_OK;
		}
		else
		{
			pBuild->Release();
		}
	}
	return hr; // Failed
}

HRESULT EnumerateDevices(REFGUID category, IEnumMoniker **ppEnum)
{
	// Create the System Device Enumerator.
	ICreateDevEnum *pDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

	if (SUCCEEDED(hr))
	{
		// Create an enumerator for the category.
		hr = pDevEnum->CreateClassEnumerator(category, ppEnum, 0);
		if (hr == S_FALSE)
		{
			hr = VFW_E_NOT_FOUND;  // The category is empty. Treat as an error.
		}
		pDevEnum->Release();
	}
	return hr;
}

void DisplayDeviceInformation(IEnumMoniker *pEnum, IMoniker **ppMoniker)
{
	IMoniker *pMoniker = NULL;

	while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
	{
		IPropertyBag *pPropBag;
		HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
		if (FAILED(hr))
		{
			pMoniker->Release();
			continue;
		}

		VARIANT var;
		VariantInit(&var);

		// Get description or friendly name.
		hr = pPropBag->Read(L"Description", &var, 0);
		if (FAILED(hr))
		{
			hr = pPropBag->Read(L"FriendlyName", &var, 0);
		}
		if (SUCCEEDED(hr))
		{
			printf("%S\n", var.bstrVal);
			VariantClear(&var);
		}

		hr = pPropBag->Write(L"FriendlyName", &var);

		// WaveInID applies only to audio capture devices.
		hr = pPropBag->Read(L"WaveInID", &var, 0);
		if (SUCCEEDED(hr))
		{
			printf("WaveIn ID: %d\n", var.lVal);
			VariantClear(&var);
		}

		hr = pPropBag->Read(L"DevicePath", &var, 0);
		if (SUCCEEDED(hr))
		{
			// The device path is not intended for display.
			printf("Device path: %S\n", var.bstrVal);
			VariantClear(&var);
		}

		*ppMoniker = pMoniker;
		pPropBag->Release();
		//pMoniker->Release();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	


#if 0
	IGraphBuilder *pGraph;
	ICaptureGraphBuilder2 *pBuild;
	IEnumMoniker *pEnum;
	IMoniker *pMoniker = NULL;
	HRESULT hr = CoInitialize(NULL);

	hr = InitCaptureGraphBuilder(&pGraph, &pBuild);
	hr = EnumerateDevices(CLSID_VideoInputDeviceCategory, &pEnum);
	if (SUCCEEDED(hr))
	{
		DisplayDeviceInformation(pEnum, &pMoniker);
		pEnum->Release();
	}

	IMediaControl *pControl;
	IMediaEvent   *pEvent;

	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

	IBaseFilter *pCap = NULL;
	hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pCap);
	if (SUCCEEDED(hr))
	{
		hr = pGraph->AddFilter(pCap, L"Capture Filter");
	}

	hr = pBuild->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
		pCap, NULL, NULL);

	hr = pControl->Run();

	long evCode = 0;
	pEvent->WaitForCompletion(INFINITE, &evCode);
	pControl->Release();
	pEvent->Release();
	pGraph->Release();
	CoUninitialize();



	CObjMgr* pMgr = new CObjMgr();

	std::shared_ptr<CObj> pObj1 = pMgr->create();
	std::cout << pObj1;
	//GetResultofPING();
	int i;
	std::cin.tie(&std::cout);
	std::cout<<"Enter a number.";
	std::cin>>i;
	int a = 0;


	std::ifstream inpputFile("C:\\Users\\zhangyabin\\Desktop\\aaa\\ETFileMD5Tool.exe",std::ios::binary);
	
	if (inpputFile.good())
	{
		std::cout<< "OK";

	}

	std::default_random_engine generator;
	std::uniform_int_distribution<int> dis(0,34);
	std::uniform_int_distribution<int> one(0,17);
	for(int i=0;i<6;i++)  
	{  
		std::cout<<dis(generator) << " " ;  
	} 

	std::cout<< one(generator) << std::endl; 

	std::cout<< "OK";

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
	std::cout << "引用计数" << pObj1.use_count() << std::endl;
	std::shared_ptr<CObj> pObj2 = pMgr->m_ptr->shared_from_this();
	std::cout << "引用计数" << pObj1.use_count() << std::endl;

	pObj1.reset();
	std::cout << "引用计数" << pObj1.use_count() << std::endl;
	std::cout << "引用计数" << pObj2.use_count() << std::endl;
	pObj2.reset();
	std::cout << "引用计数" << pObj1.use_count() << std::endl;
	std::cout << "引用计数" << pObj2.use_count() << std::endl;

	try
	{

	}
	catch (...)
	{

	}



	// Create the System Device Enumerator.
	HRESULT hr = CoInitialize(NULL);
	ICreateDevEnum *pSysDevEnum = NULL;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void **)&pSysDevEnum);
	if (FAILED(hr))
	{
		return hr;
	}

	// Obtain a class enumerator for the video compressor category.
	IEnumMoniker *pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);

	if (hr == S_OK)
	{
		// Enumerate the monikers.
		IMoniker *pMoniker = NULL;
		ULONG cFetched;
		while (pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
		{
			IPropertyBag *pPropBag;
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
				(void **)&pPropBag);
			if (SUCCEEDED(hr))
			{
				// To retrieve the filter's friendly name, do the following:
				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"FriendlyName", &varName, 0);
				if (SUCCEEDED(hr))
				{
					std::wcout << varName.bstrVal << std::endl;
					// Display the name in your UI somehow.
				}
				VariantClear(&varName);

				// To create an instance of the filter, do the following:
				IBaseFilter *pFilter;
				hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter,
					(void**)&pFilter);
				// Now add the filter to the graph. 
				//Remember to release pFilter later.
				pPropBag->Release();
			}
			pMoniker->Release();
		}
		pEnumCat->Release();
	}
	pSysDevEnum->Release();

 //   //HRESULT hr = CoInitialize(NULL);
 //   IGraphBuilder *pGraph;
 //   
 //   hr = CoCreateInstance(CLSID_FilterGraph,NULL, CLSCTX_INPROC_SERVER,IID_IGraphBuilder, (void **)&pGraph);
 //   if (FAILED(hr))
 //   {

 //   }


 //   IMediaControl *pControl;
 //   IMediaEvent   *pEvent;
 //   IMediaEventEx *pEventEx;
	//IVideoWindow* pVidWin = NULL;
	//HWND hwnd = NULL;

	//hr = pGraph->QueryInterface(IID_IVideoWindow, (void **)&pVidWin);
 //   hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
 //   hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
 //   hr = pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pEventEx);

	//pVidWin->put_Owner((OAHWND)hwnd);
	//pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	//
	//RECT rc;
	//GetClientRect(hwnd, &rc);
	//pVidWin->SetWindowPosition(0, 0, rc.right, rc.bottom);


 //   hr = pGraph->RenderFile(L"C:\\Example.avi", NULL);

 //   hr = pControl->Run();

 //   long evCode = 0;
 //   pEvent->WaitForCompletion(INFINITE, &evCode);
 //   pControl->Release();
 //   pEvent->Release();
 //   pGraph->Release();
 //   CoUninitialize();

#endif
	return 0;
}

//#ifdef 0
//HRESULT InitWindowlessVMR(
//	HWND hwndApp,                  // Window to hold the video. 
//	IGraphBuilder* pGraph,         // Pointer to the Filter Graph Manager. 
//	IVMRWindowlessControl** ppWc   // Receives a pointer to the VMR.
//	)
//{
//	if (!pGraph || !ppWc)
//	{
//		return E_POINTER;
//	}
//	IBaseFilter* pVmr = NULL;
//	IVMRWindowlessControl* pWc = NULL;
//	// Create the VMR. 
//	HRESULT hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL,
//		CLSCTX_INPROC, IID_IBaseFilter, (void**)&pVmr);
//	if (FAILED(hr))
//	{
//		return hr;
//	}
//
//	// Add the VMR to the filter graph.
//	hr = pGraph->AddFilter(pVmr, L"Video Mixing Renderer");
//	if (FAILED(hr))
//	{
//		pVmr->Release();
//		return hr;
//	}
//	// Set the rendering mode.  
//	IVMRFilterConfig* pConfig;
//	hr = pVmr->QueryInterface(IID_IVMRFilterConfig, (void**)&pConfig);
//	if (SUCCEEDED(hr))
//	{
//		hr = pConfig->SetRenderingMode(VMRMode_Windowless);
//		pConfig->Release();
//	}
//	if (SUCCEEDED(hr))
//	{
//		// Set the window. 
//		hr = pVmr->QueryInterface(IID_IVMRWindowlessControl, (void**)&pWc);
//		if (SUCCEEDED(hr))
//		{
//			hr = pWc->SetVideoClippingWindow(hwndApp);
//			if (SUCCEEDED(hr))
//			{
//				*ppWc = pWc; // Return this as an AddRef'd pointer. 
//			}
//			else
//			{
//				// An error occurred, so release the interface.
//				pWc->Release();
//			}
//		}
//	}
//	pVmr->Release();
//	return hr;
//}
//
//HRESULT init(HWND hwndApp,                  // Window to hold the video. 
//	IGraphBuilder* pGraph,         // Pointer to the Filter Graph Manager. 
//	wchar_t* wszMyFileName
//	)
//{
//	IVMRWindowlessControl *pWc = NULL;
//	HRESULT hr = InitWindowlessVMR(hwndApp, pGraph, &pWc);
//	if (SUCCEEDED(hr))
//	{
//		// Build the graph. For example:
//		pGraph->RenderFile(wszMyFileName, 0);
//		// Release the VMR interface when you are done.
//		pWc->Release();
//	}
//
//	// Find the native video size.
//	long lWidth, lHeight;
//	hr = pWc->GetNativeVideoSize(&lWidth, &lHeight, NULL, NULL);
//	if (SUCCEEDED(hr))
//	{
//		RECT rcSrc, rcDest;
//		// Set the source rectangle.
//		SetRect(&rcSrc, 0, 0, lWidth, lHeight);
//
//		// Get the window client area.
//		GetClientRect(hwndApp, &rcDest);
//		// Set the destination rectangle.
//		SetRect(&rcDest, 0, 0, rcDest.right, rcDest.bottom);
//
//		// Set the video position.
//		hr = pWc->SetVideoPosition(&rcSrc, &rcDest);
//	}
//	return hr;
//}
//#endif