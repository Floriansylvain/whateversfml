#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/System/Vector2.hpp>

#include "DebugUI.hpp"
#include "Lighting.hpp"
#include "World.hpp"

constexpr bool VSYNC = true;
constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;
constexpr int DEBUG_REFRESH_RATE_IN_MS = 250;
constexpr float ASPECT = 16.f / 9.f;

class Game {
public:
  Game();
  void run();

private:
  sf::RenderWindow window;
  sf::View worldView;

  World world;
  DebugUI debug;
  Lighting lighting;

  void onResize();
  void processEvents();
  void update(double dt);
  void render();
};

#endif // GAME_HPP
