#include "board.h"

Board::Board()
{
	cells_.begin();
	units_.begin();
	width_ = 0;
	height_ = 0;
}

Board::~Board()
{
}

void Board::init(int width, int height)
{
	width_ = width;
	height_ = height;
}

Cell& Board::cell(int row, int col)
{
	cells_.at(col * kTotalRow + row).height = col * kTotalRow + row;
	return cells_.at(col * kTotalRow + row);
}

int Board::north(int idx)
{
	if (idx < kTotalRow * 2) {
		return 0;
	}
	if (cells_.at(idx - kTotalRow ).value == 2) {
		return 1;
	}
	return 0;
}

int Board::east(int idx)
{
	if ((idx + kUnitMove) % kTotalRow == 0) {
		return 0;
	}
	if (cells_.at(idx + kUnitMove).value == 2) {
		return 1;
	}
	return 0;
}

int Board::south(int idx)
{
	if (idx > kTotalCol * kTotalRow - kTotalRow * 2) {
		return 0;
	}
	if (cells_.at(idx + kTotalRow * kUnitMove).value == 2) {
		return 1;
	}
	return 0;
}

int Board::west(int idx)
{
	if (idx % kTotalRow == 0) {
		return 0;
	}
	if (cells_.at(idx - kUnitMove).value == 2) {
		return 1;
	}
	return 0;
}

uint8_t Board::isWall(int idx)
{
	if (cells_.at(idx).value == kTileType_Wall)
	{
		return 1;
	}
	return 0;
}

uint8_t Board::isDoor(int idx)
{
	if (cells_.at(idx).value == kTileType_Door)
	{
		return 1;
	}
	return 0;
}

void Board::index2rowcol(int* row, int* col, int idx)
{

}

void Board::saveCSV(const char* csv)
{
}

int Board::findUnit(int roster_idx)
{
	return 0;
}

bool Board::checkUnitMovement(int roster_idx, int origin, int dest)
{
	return false;
}

void Board::moveUnit(int roster_idx, int origin, int dest)
{
}

void Board::killUnit(int target_idx)
{
}

int Board::euclideanDistance(int origin, int dest)
{
	return (int)sqrt(pow(origin, 2) + pow(dest, 2));
}

std::stack<int> Board::pathFind(int start, int target, int limit)
{
	return std::stack<int>();
}

int Board::randomWalkableTile()
{
	int tile = 0;
	do {
		tile = rand() % (kTotalCol * kTotalRow + 1);
	} 	while (cells_.at(tile).value != 2);
		
	return tile;
}

void Board::debugPrint()
{
}


