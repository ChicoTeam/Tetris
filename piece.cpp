#include "piece.hpp"

#include <SFML/Graphics.hpp>

namespace Tetris
{
  Piece::Piece(Board* newBoard, int newX, int newY)
  {
    board = newBoard;
    positionX = newX;
    positionY = newY;

    for(int x = 0; x < 5; ++x)
      for(int y = 0; y < 5; ++y)
	shape[x][y] = ' ';

    //Pick a shape
    int shapeNumber = sf::Randomizer::Random(1,7);

    if(shapeNumber == 1) //Cyan, long piece
    {
      shape[0][2] = 'c';
      shape[1][2] = 'c';
      shape[2][2] = 'c';
      shape[3][2] = 'c';
    }
    else if(shapeNumber == 2) // Blue, Inverse L piece
    {
      shape[1][1] = 'b';
      shape[1][2] = 'b';
      shape[2][2] = 'b';
      shape[3][2] = 'b';
    }
    else if(shapeNumber == 3) // Orange, L piece
    {
      shape[3][1] = 'o';
      shape[3][2] = 'o';
      shape[2][2] = 'o';
      shape[1][2] = 'o';
    }
    else if(shapeNumber == 4) // Yellow, square piece
    {
      shape[1][1] = 'y';
      shape[1][2] = 'y';
      shape[2][1] = 'y';
      shape[2][2] = 'y';
    }
    else if(shapeNumber == 5) // Green, S piece
    {
      shape[2][2] = 'g';
      shape[3][2] = 'g';
      shape[2][3] = 'g';
      shape[1][3] = 'g';      
    }
    else if(shapeNumber == 6) // Purple, T piece
    {
      shape[2][1] = 'p';
      shape[1][2] = 'p';
      shape[2][2] = 'p';
      shape[3][2] = 'p';
    }
    else if(shapeNumber == 7) // Red, Z piece
    {
      shape[2][2] = 'r';
      shape[1][2] = 'r';
      shape[2][3] = 'r';
      shape[3][3] = 'r';      
    }


  }

  Piece::~Piece()
  {

  }

  void Piece::Render(sf::RenderTarget &target)
  {
    for(int x = 0; x < 5; ++x)
      for(int y = 0; y < 5; ++y)
      {
	sf::Color blockColor = sf::Color::Black;
	char block = shape[x][y];
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
	  
	  sf::Shape blockShape = sf::Shape::Rectangle(positionX + x + 0.05, positionY + y + 0.05, positionX + x + 0.95, positionY + y + 0.95, blockColor);
	  target.Draw(blockShape);
	}
      }
  }

  bool Piece::Move(int dx, int dy)
  {
    for(int x = 0; x < 5; ++x)
      for(int y = 0; y < 5; ++y)
      {
	//If neither of the blocks are empty (shape and destination)
	if( shape[x][y] != ' ' && board->GetBlock(positionX + x + dx, positionY + y + dy) != ' ')
	  return false;
      }
    //There must be space if we get this far
    positionX += dx;
    positionY += dy;
    return true;
  }

  bool Piece::Rotate()
  {
    char newShape[5][5];
    
    //Rotate the piece into newShape
    for(int x = 0; x < 5; ++x)
      for(int y = 0; y < 5; ++y)
      {
	newShape[x][y] = shape[5 - y - 1][x];
      }

    //Check if the rotation actually fits
    for(int x = 0; x < 5; ++x)
      for(int y = 0; y < 5; ++y)
      {
	if( newShape[x][y] != ' ' && board->GetBlock(positionX + x, positionY + y) != ' ')
	  return false; //Abort if the rotation doesn't fit
      }


    //Apply the new rotation
    for(int x = 0; x < 5; ++x)
      for(int y = 0; y < 5; ++y)
      {
	shape[x][y] = newShape[x][y];
      }

    return true;
  }

  void Piece::Place()
  {
    for(int x = 0; x < 5; ++x)
      for(int y = 0; y < 5; ++y)
      {
	if(shape[x][y] != ' ')
	  board->SetBlock(positionX + x,positionY + y,shape[x][y]);
      }

  }
}
