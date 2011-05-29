#include "util.hpp"

#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

void Tetris::Util::DrawBlock(sf::RenderTarget &target, int x, int y, char color)
{
  sf::Color colorColor = sf::Color::Black;
  if(color != ' ')
  {
    if(color == 'r')
      colorColor = sf::Color::Red;
    if(color == 'g')
      colorColor = sf::Color::Green;
    if(color == 'b')
      colorColor = sf::Color::Blue;
    if(color == 'p')
      colorColor = sf::Color::Magenta;
    if(color == 'o')
      colorColor = sf::Color(255,127,0); //Orange
    if(color == 'c')
      colorColor = sf::Color::Cyan;
    if(color == 'y')
      colorColor = sf::Color::Yellow;
    
    sf::Shape colorShape = sf::Shape::Rectangle(x + 0.05, y + 0.05, x + 0.95, y + 0.95, colorColor);
    target.Draw(colorShape);
  }
}

std::string Tetris::Util::IntToChar( int value )
{
  std::stringstream ss;
  ss << value;
  std::string scoreString;
  ss >> scoreString;
  return scoreString;
}

