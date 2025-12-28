#include "Walls.hpp"
#include <SFML/Graphics/Vertex.hpp>

Walls::Walls() : walls(sf::PrimitiveType::Lines) {};

void Walls::add(sf::Vector2f pointA, sf::Vector2f pointB) {
  walls.append({pointA, sf::Color::Red});
  walls.append({pointB, sf::Color::Red});
  vertices.emplace_back(Wall{pointA, pointB});
};

std::vector<Wall> Walls::get() { return vertices; };

void Walls::render(sf::RenderWindow &window) { window.draw(walls); };
