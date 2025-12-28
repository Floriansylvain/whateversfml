#ifndef LIGHTING_HPP
#define LIGHTING_HPP

#include "Walls.hpp"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

struct Ray {
  sf::Vector2f origin;
  sf::Vector2f direction;
};

class Lighting {
public:
  Lighting();

  float intersects(Ray ray, Wall wall);
  sf::Vector2f updateRay(Walls &walls, sf::Vector2f &origin,
                         sf::Vector2f &targetPoint, float offset);
  void update(double dt, sf::Vector2f &playerPosition, Walls &walls);
  void render(sf::RenderWindow &window);

private:
  sf::VertexArray rayVertices;
  std::vector<sf::Vector2f> hitPoints;
  sf::Color lightColor;
};

#endif // LIGHTING_HPP