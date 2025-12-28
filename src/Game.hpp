#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "DebugUI.hpp"
#include "GridLines.hpp"
#include "Player.hpp"

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

  Player player;
  DebugUI debug;
  GridLines gridLines;

  void onResize();
  void processEvents();
  void update(double dt);
  void render();
};

#endif // GAME_HPP
