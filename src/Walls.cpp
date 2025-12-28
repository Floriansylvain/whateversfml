#include "Walls.hpp"
#include "Game.hpp"
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

Walls::Walls() : walls(sf::PrimitiveType::Lines) {
  add({1.f, 1.f}, {WIDTH - 1.f, 1.f});
  add({1.f, 1.f}, {1.f, HEIGHT - 1.f});
  add({WIDTH - 1.f, 1.f}, {WIDTH - 1.f, HEIGHT - 1.f});
  add({1.f, HEIGHT - 1.f}, {WIDTH - 1.f, HEIGHT - 1.f});

  add({1000.f, 500.f}, {1500.f, 500.f});
  add({500.f, 240.f}, {500.f, 760.f});
  add({420.f, 240.f}, {420.f, 760.f});
  add({420.f, 240.f}, {500.f, 240.f});
  add({420.f, 760.f}, {500.f, 760.f});
};

void Walls::add(sf::Vector2f pointA, sf::Vector2f pointB) {
  walls.append({pointA, sf::Color::Red});
  walls.append({pointB, sf::Color::Red});
  vertices.emplace_back(Wall{pointA, pointB});
  points.emplace_back(pointA);
  points.emplace_back(pointB);
};

std::vector<Wall> Walls::get() { return vertices; };

std::vector<sf::Vector2f> Walls::getPoints() { return points; };

void Walls::render(sf::RenderWindow &window) { window.draw(walls); };
