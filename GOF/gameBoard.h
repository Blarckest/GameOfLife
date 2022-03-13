#pragma once
#include "gameBoardAbs.h"
#include <exception>
class gameBoard:public gameBoardAbs
{
public:
	gameBoard(const gameBoard& other);
	gameBoard(gameBoard&& other);
	gameBoard(size_t columns, size_t lines);
};

