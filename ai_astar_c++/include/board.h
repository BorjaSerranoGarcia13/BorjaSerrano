#ifndef __BOARD_H__
#define __BOARD_H__ 1

#include "common_def.h"

#include <array>
#include <stack>
#include <set>
#include <vector>

const int kBoardMaxSize = 128;
const int kBoardMinSize = 16;
const int kBoardMaxUnits = 48;  // EVEN PLEASE

const int kTotalRow = 120;
const int kTotalCol = 88;

const float kWidthGrid = 8.0f;
const float kHeightGrid = 8.0f;

const int kUnitMove = 1;

enum TileType {
  kTileType_Void = 0,  // Non-walkables
  kTileType_Wall = 1,
  kTileType_Normal = 2,    // kTileType_Normal has to be the first of the walkables
  kTileType_Door = 3,
  kTileType_End = 4
};

// Possible Unit commands. Mainly for AI units
enum UnitCommand {
  kUnitCommand_None,
  kUnitCommand_Move,
  kUnitCommand_Attack,
  kUnitCommand_Use
};

// A possible result to an AI call. E.g: Move to this tile, attack
// this unit, use this item, etc . . .
struct AIResult {
  UnitCommand cmd;
  int unit_id;
  int cell_idx;
  int item_id;
};

struct Cell {
  int value;
  int height;
};


class Board {
 public:
  Board();
  ~Board();

  void init(int width = kBoardMaxSize/4, int height = kBoardMaxSize/4);

  Cell& cell(int row, int col);

  // Return the index of the north, east, south or west cells or -1
  int north(int idx);
  int east(int idx);
  int south(int idx);
  int west(int idx);

  // Return 1 if the cell is a type of wall or wall joint, 0 otherwise
  uint8_t isWall(int idx);
  
  // Return 1 if the cell is a type of door, 0 otherwise
  uint8_t isDoor(int idx);
  
  // Index to row,col
  void index2rowcol(int* row, int* col, int idx);

  // Debug export in CSV format
  void saveCSV(const char* csv);
    
  // Find a unit position (index) given its roster index
  int findUnit(int roster_idx);
  // Check if a unit can move from an origin index to a destination index
  bool checkUnitMovement(int roster_idx, int origin, int dest);
  void moveUnit(int roster_idx, int origin, int dest);
    
  // Mark a unit as dead (not targetable and selectable) and
  // remove it from the board
  void killUnit(int target_idx);  

  // Returns the euclidean, non-pathfound distance in cells.
  // Returns -1 when and index is not valid
  int euclideanDistance(int origin, int dest);  
  
  // Return a route between two indexes.
  // The optional "limit" parameter sets a size limit of the route.
  // Can be useful for partial pathfinding
  std::stack<int> pathFind(int start, int target, int limit = -1);
    
  // Returns a random, walkable tile of the board
  int randomWalkableTile(); 

  // DEBUG print
  void debugPrint();

  int width_;
  int height_;

  // Grid of Cell structures
  std::array<Cell, kTotalRow * kTotalCol> cells_;
  
  // Grid of indexes of agents. Defaults to -1
  std::array<int, kBoardMaxSize*kBoardMaxSize> units_;  
};

#endif  // __BOARD_H__
