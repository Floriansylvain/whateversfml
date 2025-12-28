#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/System/Vector2.hpp>

#include "DebugUI.hpp"
#include "GridLines.hpp"
#include "Player.hpp"
#include "Walls.hpp"

constexpr bool VSYNC = false;
constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;
constexpr int DEBUG_REFRESH_RATE_IN_MS = 250;
constexpr float ASPECT = 16.f / 9.f;

struct Ray {
  sf::Vector2f origin;
  sf::Vector2f direction;
};

class Game {
public:
  Game();
  void run();

private:
  sf::RenderWindow window;
  sf::View worldView;

  Player player;
  DebugUI debug;
  GridLines gridLines;
  Walls walls;

  sf::VertexArray rayVertices;
  std::vector<sf::Vector2f> hitPoints;
  sf::Color lightColor;

  float intersects(Ray ray, Wall wall);
  sf::Vector2f updateRay(sf::Vector2f &origin, sf::Vector2f &targetPoint,
                         float offset);

  void onResize();
  void processEvents();
  void update(double dt);
  void render();
};

#endif // GAME_HPP
