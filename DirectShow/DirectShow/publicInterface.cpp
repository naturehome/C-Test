#include "stdafx.h"
#include "publicInterface.h"


HRESULT CreateFilter(BSTR bstrLibName, REFCLSID rclsid, LPUNKNOWN pUnkOuter, REFIID riid, LPVOID* ppv)
{
	// Load the library (bstrlibname should have the fullpath)
	HINSTANCE hDLL = CoLoadLibrary(bstrLibName, TRUE);

	if (hDLL == NULL)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// Get the function pointer
	typedef HRESULT(WINAPI* PFNDllGetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID* ppv);

	PFNDllGetClassObject pfnDllGetClassObject = (PFNDllGetClassObject)GetProcAddress(hDLL, "DllGetClassObject");
	if (!pfnDllGetClassObject)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// Get the class faftory
	CComPtr<IClassFactory> pFactory;
	HRESULT hr = pfnDllGetClassObject(rclsid, IID_IClassFactory, (LPVOID*)&pFactory);
	if (hr != S_OK)
	{
		return hr;
	}

	// Create object instance
	return pFactory->CreateInstance(pUnkOuter, riid, ppv);
}
