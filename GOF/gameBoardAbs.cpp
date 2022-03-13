#include "gameBoardAbs.h"
#include <limits>
#include <exception>
#include <string>

gameBoardAbs::gameBoardAbs(size_t columns, size_t lines) :nbOfLines(lines), nbOfColumns(columns)
{
	if (lines > ULLONG_MAX / columns)
	{
		//throw std::exception("Dimensions too big");
		grid = new bool[10 * 10]();
		nbOfLines = 10;
		nbOfColumns = 10;
		return;
	}
	grid = new bool[lines * columns]();
}

gameBoardAbs::gameBoardAbs(const gameBoardAbs& other):
	nbOfColumns(other.nbOfColumns),nbOfLines(other.nbOfLines)
{
	grid = new bool[nbOfColumns * nbOfLines]();
	std::memcpy(grid, other.grid, sizeof(bool) * nbOfColumns * nbOfLines);
}

gameBoardAbs::gameBoardAbs(gameBoardAbs&& other):
	nbOfColumns(other.nbOfColumns), nbOfLines(other.nbOfLines)
{
	delete[] grid;
	grid = other.grid;
	other.grid = nullptr;
}

gameBoardAbs::~gameBoardAbs()
{
	delete[] grid;
}

bool gameBoardAbs::getAt(size_t columns, size_t line) const
{
	return grid[indexAt(columns,line)];
}

void gameBoardAbs::setAt(size_t column, size_t line, bool newVal)
{
	grid[indexAt(column, line)] = newVal;
}

const size_t gameBoardAbs::getNbOfLines() const
{
	return nbOfLines;
}

const size_t gameBoardAbs::getNbOfcolumns() const
{
	return nbOfColumns;
}

size_t gameBoardAbs::indexAt(size_t column, size_t line)const
{
	return column*nbOfLines+line;
}
