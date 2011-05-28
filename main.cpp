#include <SFML/Graphics.hpp>

#include "tetris.hpp"

int main()
{
  //Create the rendering window
  sf::RenderWindow window(sf::VideoMode(600,800, 32), "Tetris");

  //Play the game
  while(window.IsOpened())
    Tetris::Tetris(window);

  return 0;
}
