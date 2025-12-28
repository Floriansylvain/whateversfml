#ifndef WORLD_HPP
#define WORLD_HPP

#include "GridLines.hpp"
#include "Player.hpp"
#include "Walls.hpp"

struct World {
  World();
  World(Player player, GridLines gridLines, Walls walls);

  Player player;
  GridLines gridLines;
  Walls walls;

  void update(double dt, sf::RenderWindow &window, const sf::View &view);
  void render(sf::RenderWindow &window);
};

#endif // WORLD_HPP
