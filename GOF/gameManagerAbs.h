#pragma once
#include "gameBoard.h"
#include <memory>
#include <unordered_set>
#include "genInfo.h"
class gameManagerAbs
{
public:
	gameManagerAbs(size_t columns, size_t lines);
	gameManagerAbs(const gameManagerAbs& other) = delete;
	gameManagerAbs(const gameManagerAbs&& other) = delete;
	virtual ~gameManagerAbs();
	virtual std::unique_ptr<genInfo> nextGen() = 0;
	virtual void initPoint(size_t column, size_t line, bool newVal);
	virtual bool getAt(size_t column, size_t line)const;
	const size_t getNbOfLines() const;
	const size_t getNbOfColumns() const;
	virtual void resetGameBoard();
protected:
	size_t nbOfLines;
	size_t nbOfColumns;
	virtual bool isGoingTolive(size_t column, size_t line) const = 0 ;
	gameBoardAbs* m_gameBoard;
	virtual void modifyAt(size_t column, size_t line, bool newVal);
};

