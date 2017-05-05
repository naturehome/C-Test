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
				mCells[i][j] = src.mCells[i][j]->Clone();
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
	if (inPiece)
		mCells[x][y] = inPiece->Clone();
}

GamePiece* GameBoard::getPieceAt(size_t x, size_t y)
{
	return mCells[x][y];
}

const GamePiece* GameBoard::getPieceAt(size_t x, size_t y) const
{
	return mCells[x][y];
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

