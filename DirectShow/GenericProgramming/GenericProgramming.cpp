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
	return mCells[x][y];
}

const GamePiece* GameBoard::getPieceAt(size_t x, size_t y) const
{
	return mCells[x][y];
}

#include <type_traits>
#include <iostream>
#include <string>

#include <memory>
#include <regex>
#include <algorithm>
#include <functional>
#include <array>

int _tmain(int argc, _TCHAR* argv[])
{
	//×Ö·ûÌæ»»
	std::string strWindowPath = "E:\\FileRecv\\images\\images\\btn_13.png";
	//std::for_each(strWindowPath.begin(), strWindowPath.end(), [](char& c){ c = (c == '\\' ? '/' : c); });


	std::replace_if(strWindowPath.begin(), strWindowPath.end(), std::bind(std::equal_to<char>(), std::placeholders::_1, '\\'), '/');

	std::replace(strWindowPath.begin(), strWindowPath.end(), '\\', '/');
	////ÅÐ¶Ï»ØÎÄ
	//std::string str("helloolleh");
	//bool bret = std::equal(str.begin(), str.begin() + str.length() / 2, str.rbegin());
	//
	////×Ö·û´®·­×ª
	//std::reverse(strWindowPath.begin(), strWindowPath.end());
	std::cout << strWindowPath << std::endl;

	const std::size_t N = 100;
	int* a = new int[N];
	int* end = a + N;
	for (std::ptrdiff_t i = N; i > 0; --i)
		std::cout << (*(end - i) = i) << ' ';
	delete[] a;
	
	return 0;
}

