#ifndef WALLS_HPP
#define WALLS_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

struct Wall {
  sf::Vector2f start;
  sf::Vector2f end;
};

class Walls {
public:
  Walls();

  void add(sf::Vector2f pointA, sf::Vector2f pointB);
  std::vector<Wall> get();
  std::vector<sf::Vector2f> getPoints();

  void render(sf::RenderWindow &window);

private:
  sf::VertexArray walls;
  std::vector<Wall> vertices;
  std::vector<sf::Vector2f> points;
};

#endif // WALLS_HPP
