#include "World.hpp"
#include "Game.hpp"
#include "GridLines.hpp"
#include "Player.hpp"
#include "Walls.hpp"

World::World()
    : player(15.f, sf::Color::Green), gridLines(WIDTH, HEIGHT, 20.f),
      walls() {};

World::World(Player player, GridLines grid, Walls walls)
    : player(player), gridLines(grid), walls(walls) {}

void World::update(double dt, sf::RenderWindow &window, const sf::View &view) {
  player.update(dt, window, view);
}

void World::render(sf::RenderWindow &window) {
  gridLines.render(window);
  player.render(window);
  walls.render(window);
}
