#ifndef GRIDLINES_HPP
#define GRIDLINES_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class GridLines {
public:
  GridLines(float width, float height, float spacing = 20.f);

  void render(sf::RenderWindow &window) const;

private:
  sf::VertexArray lines;
};

#endif // GRIDLINES_HPP
