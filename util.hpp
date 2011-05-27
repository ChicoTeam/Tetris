#pragma once

#include <SFML/Graphics.hpp>

namespace Tetris
{
  namespace Util
  {
    void DrawBlock(sf::RenderTarget &target, int x, int y, char color);
  }
}
