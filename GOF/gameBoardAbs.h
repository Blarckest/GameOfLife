#pragma once
#include <limits>
class gameBoardAbs
{
public:
	gameBoardAbs(const gameBoardAbs& other);
	gameBoardAbs(gameBoardAbs&& other);
	virtual ~gameBoardAbs();
	virtual bool getAt(size_t column, size_t line) const;
	virtual void setAt(size_t column, size_t line, bool newVal);
	const size_t getNbOfLines() const;
	const size_t getNbOfcolumns() const;
protected:
	gameBoardAbs(size_t columns, size_t lines);
	virtual size_t indexAt(size_t column, size_t line) const;
	bool* grid = nullptr;
	size_t nbOfLines;
	size_t nbOfColumns;
};

