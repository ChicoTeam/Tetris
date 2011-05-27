#pragma once
#include <boost/multi_array.hpp>
#include <SFML/Graphics.hpp>

namespace Tetris
{
  typedef boost::multi_array<char, 2> boardType;

  class Board
  {
  public:
    Board(int newWidth, int newHeight);
    ~Board();
  
    void Clear();
    void Randomise();
    char GetBlock(int x,int y);
    bool SetBlock(int x, int y, char val);
    void Render(sf::RenderTarget &target);
    int CheckRows();
  private:
    int width;
    int height;
    boardType* board;
  };
}
