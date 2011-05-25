#pragma once

#include <SFML/Graphics.hpp>
#include "board.hpp"

namespace Tetris
{
  class Piece
  {
  public:
    Piece(Board* newBoard, int newX, int newY);
    ~Piece();

    void Render(sf::RenderTarget &target);
    bool Move(int dx, int dy);
    bool Rotate();
    void Place();
  private:
    Board* board;
    char shape[5][5];
    int positionX;
    int positionY;
  };
}
