// GenericProgramming.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


class GamePiece
{
public:
	GamePiece* Clone();
};
class GameBoard
{
public:
	GameBoard(size_t inWidth = kDefaultWidth, size_t inHeight = kDefaultHeight);
	GameBoard(const GameBoard& src);
	virtual ~GameBoard();
	GameBoard& operator=(const GameBoard& rhs);

	void setPieceAt(size_t x, size_t y, const GamePiece* inPiece);
	GamePiece* getPieceAt(size_t x, size_t y);
	const GamePiece* getPieceAt(size_t x, size_t y) const;

	size_t getWidth() const{ return mWidth; }
	size_t getHeight() const{ return mHeight; }

	static const size_t kDefaultWidth = 10;
	static const size_t kDefaultHeight = 10;

protected:
	void CopyFrom(const GameBoard& src);
	void initializeCells();
	void cleanCells();
private:
	GamePiece*** mCells;
	size_t mWidth;
	size_t mHeight;
};

GameBoard::GameBoard(size_t inWidth, size_t inHeight) :mWidth(inWidth), mHeight(inHeight)
{
	initializeCells();
}

GameBoard::GameBoard(const GameBoard& src)
{
	CopyFrom(src);
}

GameBoard::~GameBoard(){
	cleanCells();
}

void GameBoard::CopyFrom(const GameBoard& src)
{
	mWidth = src.mWidth;
	mHeight = src.mHeight;

	initializeCells();

	for (size_t i = 0; i < mWidth; i++)
	{
		for (size_t j = 0; j < mHeight; j++)
			if (mCells[i][j] != nullptr)
			{
				//mCells[i][j] = src.mCells[i][j]->Clone();
			}	
	}
}

void GameBoard::initializeCells()
{
	mCells = new GamePiece**[mWidth];
	for (size_t i = 0; i < mWidth; i++)
	{
		mCells[i] = new GamePiece*[mHeight];
		for (size_t j = 0; j < mHeight; j++)
		{
			mCells[i][j] = nullptr;
		}
	}
}

void GameBoard::cleanCells()
{
	for (size_t i = 0; i < mWidth; i++)
	{
		for (size_t j = 0; j < mHeight; j++)
		{
			delete mCells[i][j];
		}
		delete [] mCells[i];
	}
	delete[] mCells;

	mCells = nullptr;
}


GameBoard& GameBoard::operator = (const GameBoard& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	cleanCells();
	CopyFrom(rhs);
	return *this;
}

void GameBoard::setPieceAt(size_t x, size_t y, const GamePiece* inPiece)
{
	//if (inPiece)
	//	mCells[x][y] = inPiece->Clone();
}

GamePiece* GameBoard::getPieceAt(size_t x, size_t y)
{
	if (x < mWidth && y < mHeight)
		return mCells[x][y];
	return nullptr;
}

const GamePiece* GameBoard::getPieceAt(size_t x, size_t y) const
{
	if (x < mWidth && y < mHeight)
		return mCells[x][y];
	return nullptr;
}

#include <type_traits>
#include <iostream>
#include <string>

#include <memory>
#include <regex>
#include <algorithm>
#include <functional>
#include <array>
#include <typeinfo>
#include "sdl/SDL.h"
#include <atomic>
#include <thread>
#include <mutex>
#include <locale>
#include <numeric>
class Data
{
public:
	void operator()()
	{
		std::call_once(mOnceFlag, &Data::init, this);
		std::cout << "Work" << std::endl;
	}
protected:
	void init()
	{
		std::cout << "init " << std::endl;
		pMemory = new char[1024];
	}

	mutable std::once_flag  mOnceFlag;
	mutable char* pMemory;
};

template <typename chr>
class StringBuilder {
	typedef std::basic_string<chr> string_t;
	typedef std::list<string_t> container_t; // Reasons not to use vector below. 
	typedef typename string_t::size_type size_type; // Reuse the size type in the string.
	container_t m_Data;
	size_type m_totalSize;
	void append(const string_t &src) {
		m_Data.push_back(src);
		m_totalSize += src.size();
	}
	// No copy constructor, no assignement.
	StringBuilder(const StringBuilder &);
	StringBuilder & operator = (const StringBuilder &);
public:
	StringBuilder(const string_t &src) {
		if (!src.empty()) {
			m_Data.push_back(src);
		}
		m_totalSize = src.size();
	}
	StringBuilder() {
		m_totalSize = 0;
	}
	// TODO: Constructor that takes an array of strings.


	StringBuilder & Append(const string_t &src) {
		append(src);
		return *this; // allow chaining.
	}
	// This one lets you add any STL container to the string builder. 
	template<class inputIterator>
	StringBuilder & Add(const inputIterator &first, const inputIterator &afterLast) {
		// std::for_each and a lambda look like overkill here.
		// <b>Not</b> using std::copy, since we want to update m_totalSize too.
		for (inputIterator f = first; f != afterLast; ++f) {
			append(*f);
		}
		return *this; // allow chaining.
	}
	StringBuilder & AppendLine(const string_t &src) {
		static chr lineFeed[] { 10, 0 }; // C++ 11. Feel the love!
		m_Data.push_back(src + lineFeed);
		m_totalSize += 1 + src.size();
		return *this; // allow chaining.
	}
	StringBuilder & AppendLine() {
		static chr lineFeed[] { 10, 0 };
		m_Data.push_back(lineFeed);
		++m_totalSize;
		return *this; // allow chaining.
	}

	// TODO: AppendFormat implementation. Not relevant for the article. 

	// Like C# StringBuilder.ToString()
	// Note the use of reserve() to avoid reallocations. 
	string_t ToString() const {
		string_t result;
		// The whole point of the exercise!
		// If the container has a lot of strings, reallocation (each time the result grows) will take a serious toll,
		// both in performance and chances of failure.
		// I measured (in code I cannot publish) fractions of a second using 'reserve', and almost two minutes using +=.
		result.reserve(m_totalSize + 1);
		//	result = std::accumulate(m_Data.begin(), m_Data.end(), result); // This would lose the advantage of 'reserve'
		for (auto iter = m_Data.begin(); iter != m_Data.end(); ++iter) {
			result += *iter;
		}
		return result;
	}

	// like javascript Array.join()
	string_t Join(const string_t &delim) const {
		if (delim.empty()) {
			return ToString();
		}
		string_t result;
		if (m_Data.empty()) {
			return result;
		}
		// Hope we don't overflow the size type.
		size_type st = (delim.size() * (m_Data.size() - 1)) + m_totalSize + 1;
		result.reserve(st);
		// If you need reasons to love C++11, here is one.
		struct adder {
			string_t m_Joiner;
			adder(const string_t &s) : m_Joiner(s) {
				// This constructor is NOT empty.
			}
			// This functor runs under accumulate() without reallocations, if 'l' has reserved enough memory. 
			string_t operator()(string_t &l, const string_t &r) {
				l += m_Joiner;
				l += r;
				return l;
			}
		} adr(delim);
		auto iter = m_Data.begin();
		// Skip the delimiter before the first element in the container.
		result += *iter;
		return std::accumulate(++iter, m_Data.end(), result, adr);
	}

}; // class StringBuilder


int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::string> vec = { "hello", " ", "world" };
	std::string s;
	s = std::accumulate(vec.begin(), vec.end(), s);
	std::cout << s << std::endl;

	return 0;


	std::cout.sync_with_stdio(true);
	Data d1;
	std::thread t1{ std::ref(d1) };
	std::thread t2{ std::ref(d1) };
	std::thread t3{ std::ref(d1) };

	t1.join();
	t2.join();
	t3.join();

	size_t pos = 0;
	int a = 500;
	int b = 600;
	float c = 0.6f;
	double d = 0.1;
	char e = 'a';
	unsigned char f = 'b';

	std::cout << typeid(pos).name() << std::endl;
	std::cout << typeid(pos - a).name() << std::endl;
	std::cout << typeid(a - b).name() << std::endl;
	std::cout << typeid(c - pos).name() << std::endl;
	std::cout << typeid(c - a).name() << std::endl;

	std::cout << typeid(d - pos).name() << std::endl;
	std::cout << typeid(d - a).name() << std::endl;

	std::cout << typeid(d - c).name() << std::endl;

	std::cout << typeid(e - a).name() << std::endl;

	std::cout << typeid(f - a).name() << std::endl;

	std::cout << typeid(f - d).name() << std::endl;
	std::cout << pos - a << std::endl;

	std::cout << a - b << std::endl;
	
	size_t pos1 = std::string::npos;
	//×Ö·ûÌæ»»
	std::string strWindowPath = "E:\\FileRecv\\images\\images\\btn_13.png";
	//std::for_each(strWindowPath.begin(), strWindowPath.end(), [](char& c){ c = (c == '\\' ? '/' : c); });
	std::cout << typeid(strWindowPath).hash_code() << std::endl;

	bool bequal = std::equal_to<char>()('a', 'b');

	std::replace_if(strWindowPath.begin(), strWindowPath.end(), std::bind(std::equal_to<char>(), std::placeholders::_1, '\\'), '/');

	std::replace(strWindowPath.begin(), strWindowPath.end(), '\\', '/');


	std::atomic<int> count(0);

	////ÅÐ¶Ï»ØÎÄ
	//std::string str("helloolleh");
	//bool bret = std::equal(str.begin(), str.begin() + str.length() / 2, str.rbegin());
	//
	////×Ö·û´®·­×ª
	//std::reverse(strWindowPath.begin(), strWindowPath.end());
	std::cout << strWindowPath << std::endl;

	//const std::size_t N = 100;
	//int* a = new int[N];
	//int* end = a + N;
	//for (std::ptrdiff_t i = N; i > 0; --i)
	//	std::cout << (*(end - i) = i) << ' ';
	//delete[] a;
	
	std::wcout.imbue(std::locale(""));
	std::wcout << 32767 << std::endl;
	return 0;
}
