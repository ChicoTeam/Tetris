#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace Tetris
{
  namespace Util
  {
    void DrawBlock(sf::RenderTarget &target, int x, int y, char color);
    std::string IntToString( int value );
  }
}
