#include "board.hpp"

#include <boost/multi_array.hpp>
#include <SFML/Graphics.hpp>


namespace Tetris
{
  Board::Board(int newWidth, int newHeight)
  {
    width = newWidth;
    height = newHeight;

    board = new boardType(boost::extents[width][height]);
    Clear(); //Clear ourselves to initalize the board
  }

  Board::~Board()
  {
    delete board;
  }

  void Board::Clear()
  {
    for(boardType::index x = 0; x != width; ++x)
      for(boardType::index y = 0; y != height; ++y)
	SetBlock(x,y,' ');
  }

  void Board::Randomise()
  {
    for(boardType::index x = 0; x != width; ++x)
    {
      for(boardType::index y = 0; y != height; ++y)
      {
	char colours[] = "rgbpo";
	char colour = colours[sf::Randomizer::Random(0,4)];
	SetBlock(x,y,colour);
      }
    }
  }

  char Board::GetBlock(int x, int y)
  {
    //Check the block is valid
    if( x < 0 || x == width || y < 0 || y == height )
      return 0; //null

    return (*board)[x][y];
  }

  bool Board::SetBlock(int x, int y, char val)
  {
    //Check the block is valid
    if( x < 0 || x == width || y < 0 || y == height )
      return false;

    (*board)[x][y] = val;
    return true;
  }

  void Board::Render(sf::RenderTarget &target)
  {
    sf::Shape bg = sf::Shape::Rectangle(0,0,width,height,sf::Color::White);
    target.Draw(bg);

    for(boardType::index x = 0; x != width; ++x)
    {
      for(boardType::index y = 0; y != height; ++y)
      {
	char block = GetBlock(x,y);
	sf::Color blockColor;

	if(block != ' ')
	{
	  if(block == 'r')
	    blockColor = sf::Color::Red;
	  if(block == 'g')
	    blockColor = sf::Color::Green;
	  if(block == 'b')
	    blockColor = sf::Color::Blue;
	  if(block == 'p')
	    blockColor = sf::Color(255,0,255); //Purple
	  if(block == 'o')
	    blockColor = sf::Color(255,165,0); //Orange
	  if(block == 'c')
	    blockColor = sf::Color::Cyan;
	  if(block == 'y')
	    blockColor = sf::Color(255,255,0); //Yellow

	  sf::Shape blockShape = sf::Shape::Rectangle(x+0.05,y+0.05,x+0.95,y+0.95,blockColor);
	  target.Draw(blockShape);
	}
      }
    }
  }

  bool Board::CheckRows()
  {
    bool clearedRow = false;
    for( int y = (height - 1); y >= 0; --y)
    {
      bool full = true;
      for( int x = 0; x < width; ++x)
      {
	if(GetBlock(x,y) == ' ')
	  full = false;
      }

      if(full)
      {
	clearedRow = true;
	//Shift all the rows down
	for( int y2 = y; y2 >= 0; --y2)
	{
	  for( int x2 = 0; x2 < width; ++x2)
	  {
	    //Copy rows down unless we're the top row, top row is wiped
	    if(y2 > 0)
	    {
	      SetBlock(x2,y2, GetBlock(x2,y2-1));
	    }
	    else
	    {
	      SetBlock(x2,y2,' '); //Clear the row
	    }
	  }
	}
      }
    }
    return clearedRow;
  }
}
