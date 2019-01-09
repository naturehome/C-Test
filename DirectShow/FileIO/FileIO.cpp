// FileIO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <hash_map>

template <unsigned int n>
struct factorial
{
	enum
	{
		value = n*factorial<n - 1>::value
	};
};

template <>
struct factorial<0>
{
	enum
	{
		value = 1
	};
};


class Person
{
public:
	void Walk()                //普通人的“走”
	{
		std::cout << "Person::Walk I am an Ordinary People." << std::endl;
	};
};

class Student : public Person
{
public:
	void Walk()                //学生的“走”
	{
		std::cout << "Student::Walk I am a student." << std::endl;
	};
};

int _tmain(int argc, _TCHAR* argv[])
{

	Student s;
	Person* pp = &s;
	pp->Walk();

	Student* ps = &s;
	ps->Walk();


	std::ofstream os("foo.txt");
	if (os.is_open()){
		os << "hello world!";
		char data[] = "foo";
		os.write(data, 3);
	}

//	std::ifstream ifs("foo.txt"); // open file "foo.txt" for reading only
//	std::ofstream ofs("foo.txt"); // open file "foo.txt" for writing only
//	std::fstream iofs("foo.txt"); // open file "foo.txt" for reading and writing

//	std::ifstream ifs;
//	ifs.open("foo.txt");

//	std::ofstream ofs;
//	ofs.open("foo.txt");

//	std::fstream iofs;
//	iofs.open("foo.txt");

	std::ifstream ifs("fooo.txt");

	if (!ifs.is_open())
		std::cout << "Open file failed File:fooo.txt" << std::endl;


	std::ifstream is("foo1.txt");
	//std::string firstname, lastname;
	//int age, bmonth, bday, byear;
	std::string whole_file;
	/*while (is >> firstname >> lastname >> age >> bmonth >> bday >> byear)	
	{
		std::cout << firstname << std::endl;
		std::cout << lastname << std::endl;
		std::cout << bmonth << std::endl;
		std::cout << bday << std::endl;
		std::cout << byear << std::endl;
	}*/

	is.seekg(0, std::ios::end);
	size_t fileSize = is.tellg();
	whole_file.reserve(is.tellg());

	is.seekg(0, std::ios::beg);
	whole_file.assign(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>());

	std::string strOriginImageUrl = "http://wx2.sinaimg.cn/mw690/e5298966gy1fg82zb9oehj20b4066mxs.jpg";

	std::size_t pos = strOriginImageUrl.find_last_of('/');
	std::string imageName = strOriginImageUrl.substr(pos + 1);


	return 0;
}

