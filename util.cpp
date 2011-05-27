#include "util.hpp"

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
      colorColor = sf::Color(255,0,255); //Purple
    if(color == 'o')
      colorColor = sf::Color(255,165,0); //Orange
    if(color == 'c')
      colorColor = sf::Color::Cyan;
    if(color == 'y')
      colorColor = sf::Color(255,255,0); //Yellow
    
    sf::Shape colorShape = sf::Shape::Rectangle(x + 0.05, y + 0.05, x + 0.95, y + 0.95, colorColor);
    target.Draw(colorShape);
  }
}
