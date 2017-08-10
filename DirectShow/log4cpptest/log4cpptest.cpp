// log4cpptest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#if 0
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include <fstream>
#include <random>
#include <array>
#include <algorithm>
#include <numeric>
#ifdef _DEBUG
#pragma comment(lib,"log4cpp/log4cppD.lib")
#else
#pragma comment(lib,"log4cpp/log4cppLib.lib")
#endif
#endif

#include "../stringTestDll/stringTestDll.h"

#pragma comment(lib,"../commfiles/bin/stringTestDll.lib")


const unsigned int ARRAYSIZE = 10;
#include <vector>
#include <cmath>
#include <strstream>
#define M_PI       3.14159265358979323846
#define M_PI_4     0.785398163397448309616

double func(double φf, double φi, double λf, double λi)
{
	double result	= tan(M_PI_4 + (φf / 2));
	double result1	= tan(M_PI_4 + (φi / 2));
	double dividend = log(result / result1); 
	double divisor	= λf - λi;
	return atan(divisor / dividend);
}

void func(){
	// String to tokenize
	std::string str{ "The quick brown fox" };
	// Vector to store tokens
	std::vector<std::string> tokens;

	for (auto i = std::strtok(&str[0], " "); i != NULL; i = strtok(NULL, " "))
		tokens.push_back(i);

}
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <codecvt>
#include <locale>

template <class T>
std::string to_string(const T& t)
{
	std::ostringstream oss;
	oss << t;
	return oss.str();
}

void func1()
{
	// String to tokenize
	const std::string str("The  quick \tbrown \nfox");
	std::istringstream is(str);
	// Vector to store tokens
	const std::vector<std::string> tokens = std::vector<std::string>(
		std::istream_iterator<std::string>(is),
		std::istream_iterator<std::string>());

	std::copy(cbegin(tokens), cend(tokens), std::ostream_iterator<std::string>(std::cout, "\n"));
}

void func2()
{
	std::string input_str = "this is a -string-, which is a sequence based on the -char- type.";
	std::wstring input_wstr = L"this is a -wide- string, which is based on the -wchar_t- type.";

	// conversion
	std::wstring str_turned_to_wstr = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(input_str);
	std::string wstr_turned_to_str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(input_wstr);
}


using convert_t = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_t, wchar_t> strconverter;

std::string to_string(std::wstring wstr)
{
	return strconverter.to_bytes(wstr);
}

std::wstring to_wstring(std::string str)
{
	return strconverter.from_bytes(str);
}
#include <future>               // std::async, std::future
#include <thread>
template <typename F>
auto async_deffered(F&& func) -> std::future < decltype(func()) >
{
	using result_type = decltype < func() > ;
	auto promise = std::promise<result_type>();
	auto future = promise.get_future();

	std::thread(std::bind([=](std::promise<result_type>& promise){
		try
		{
			promise.set_value(func());
		}
		catch (...)
		{
			promise.set_exception(std::current_exception());
		}
	}, std::move(promise))).detach();
	return future;
}


#include <iostream>
using namespace std;


void merge(int low, int mid, int high, vector<int>&num)
{
	vector<int> copy(num.size());
	int h, i, j, k;
	h = low;
	i = low;
	j = mid + 1;

	while ((h <= mid) && (j <= high))
	{
		if (num[h] <= num[j])
		{
			copy[i] = num[h];
			h++;
		}
		else
		{
			copy[i] = num[j];
			j++;
		}
		i++;
	}
	if (h>mid)
	{
		for (k = j; k <= high; k++)
		{
			copy[i] = num[k];
			i++;
		}
	}
	else
	{
		for (k = h; k <= mid; k++)
		{
			copy[i] = num[k];
			i++;
		}
	}
	for (k = low; k <= high; k++)
		swap(num[k], copy[k]);
}


void merge_sort(int low, int high, vector<int>& num)
{
	int mid;
	if (low<high)
	{
		mid = low + (high - low) / 2;
		auto future1 = std::async(std::launch::deferred, [&]()
		{
			merge_sort(low, mid, num);
		});
		auto future2 = std::async(std::launch::deferred, [&]()
		{
			merge_sort(mid + 1, high, num);
		});

		future1.get();
		future2.get();
		merge(low, mid, high, num);
	}
}



int _tmain(int argc, _TCHAR* argv[])
{

	std::vector<int> Master;

 #pragma omp for nowait
	for (size_t i = 0; i < 1000000; ++i)
	{
		Master.push_back(i);
	}



	const char * C_String = "Thisisalineoftextw";
	const char * C_Problem_String = "This is a line of text";
	std::string Std_String("This is a second line of text w");
	std::string Std_Problem_String("This is a second line of");

	std::cout << "String Length: " << Std_String.length() << '\n';
	std::cout << "String Length: " << Std_Problem_String.length() << '\n';

	std::cout << "CString Length: " << strlen(C_String) << '\n';
	std::cout << "CString Length: " << strlen(C_Problem_String) << '\n';

	std::cout << "String Length: " << Std_String.size() << '\n';
	std::cout << "String Length: " << Std_Problem_String.size() << '\n';
#if 0
	std::ofstream file("test1.log");
	std::streambuf* pOutBuffer = std::cout.rdbuf(file.rdbuf());
	std::streambuf* pErrBuffer = std::cerr.rdbuf(file.rdbuf());

	std::cout << "no error" << std::endl;
	std::cerr << "error" << std::endl;

	std::cout.rdbuf(pOutBuffer);
	std::cerr.rdbuf(pErrBuffer);

	std::default_random_engine generator;
	std::vector<int> a(ARRAYSIZE,0);
	std::vector<int> b(ARRAYSIZE, 0);

	std::uniform_int_distribution<int> dis(0, 52);
	for(int i=0;i < 10;i++)  
	{  
		a[i] = dis(generator);
		b[i] = dis(generator);
	} 

	std::for_each(a.begin(), a.end(), [=](int e){std::cout << e << " "; });
	std::cout << std::endl;

	std::for_each(b.begin(), b.end(), [=](int e){std::cout << e << " "; });
	std::cout << std::endl;

	std::vector<int> c;

	std::copy(a.begin(),a.end(),std::back_inserter(c));
	std::copy(b.begin(),b.end(),std::back_inserter(c));
	std::stable_sort(c.begin(),c.end());

	std::for_each(c.begin(), c.end(), [=](int e){std::cout << e << " "; });
	std::cout << std::endl;

	a.clear();
	b.clear();
	bool flag = 1;

	for(auto itor = c.begin(); itor != c.end();)
	{
		if (flag)
		{
			a.push_back(*itor);
			itor++;
			if (itor != c.end())
				b.push_back(*itor);
			else
				break;

			flag = 0;
		}
		else
		{
			b.push_back(*itor);
			itor++;
			if (itor != c.end())
				a.push_back(*itor);
			else
				break;
			flag = 1;
		}
		itor++;
	}

	int suma = std::accumulate(a.begin(),a.end(),0);
	int sumb = std::accumulate(b.begin(),b.end(),0);
	std::cout << "array A = " << suma << std::endl;
	std::cout << "array b = " << sumb << std::endl;
	std::cout << "array b - array A = " << sumb -suma << std::endl;


	log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
	appender1->setLayout(new log4cpp::BasicLayout());

	log4cpp::Appender *appender2 = new log4cpp::FileAppender("default", "program.log");
	appender2->setLayout(new log4cpp::BasicLayout());

	log4cpp::Category& root = log4cpp::Category::getRoot();
	root.setPriority(log4cpp::Priority::DEBUG);
	root.addAppender(appender1);

	log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));
	sub1.addAppender(appender2);

	// use of functions for logging messages
	root.error("root error");
	root.info("root info");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::INFO << "Streamed root info";
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

	// or this way:
	root.errorStream() << "Another streamed error";


	std::string initFileName = "log4cpp.properties";
	log4cpp::PropertyConfigurator::configure(initFileName);

	log4cpp::Category& root = log4cpp::Category::getRoot();

	log4cpp::Category& sub1 =
		log4cpp::Category::getInstance(std::string("sub1"));

	log4cpp::Category& sub2 =
		log4cpp::Category::getInstance(std::string("sub1.sub2"));

	root.warn("Storm is coming");

	sub1.debug("Received storm warning");
	sub1.info("Closing all hatches");

	sub2.debug("Hiding solar panels");
	sub2.error("Solar panels are blocked");
	sub2.debug("Applying protective shield");
	sub2.warn("Unfolding protective shield");
	sub2.info("Solar panels are shielded");

	sub1.info("All hatches closed");

	root.info("Ready for storm.");

	log4cpp::Category::shutdown();
#endif
	return 0;
}

