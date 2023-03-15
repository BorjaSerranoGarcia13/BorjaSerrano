#ifndef __LOADER_H__
#define __LOADER_H__ 1

#include "board.h"
#include "common_def.h"


// Load a cost map image where:
// - White pixel: walkable
// - Black pixel: non-walkable
static ErrorCode BoardFromImage(Board* board, const char* filename) {
  if (filename == nullptr) return kErrorCode_SRCNullPointer;
  if (board == nullptr) return kErrorCode_DataNullPointer;

  sf::Texture texture;
  if (!texture.loadFromFile(filename))
  {
      return kErrorCode_File;
  }
  sf::Image image = texture.copyToImage();
  sf::Color color;

  board->init(texture.getSize().x, texture.getSize().y);

  for (int col = 0; col < texture.getSize().y; ++col) {
      for (int row = 0; row < texture.getSize().x; ++row) {
          color = image.getPixel(row, col);
          if (color == sf::Color::White) {
              // White
              board->cell(row, col).value = kTileType_Normal;
          }
          else if (color == sf::Color::Black) {
              // Black
              board->cell(row, col).value = kTileType_Wall;
          }
          else {
              board->cell(row, col).value = kTileType_Wall;
          } 
      }
  }  
  return kErrorCode_Ok;
}

#endif
