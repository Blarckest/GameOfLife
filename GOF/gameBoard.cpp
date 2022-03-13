#include "gameBoard.h"

gameBoard::gameBoard(const gameBoard& other):gameBoardAbs(other)
{
}

gameBoard::gameBoard(gameBoard&& other):gameBoardAbs(std::move(other))
{
}

gameBoard::gameBoard(size_t columns, size_t lines):gameBoardAbs(columns,lines)
{
}
