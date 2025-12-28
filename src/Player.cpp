#include "Player.hpp"
#include "Game.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/View.hpp>

Player::Player(float size, sf::Color color) : circleShape(size) {
  circleShape.setFillColor(color);
}

void Player::update(double dt, sf::RenderWindow &window, const sf::View &view) {
  auto shapeRadius = circleShape.getRadius();
  auto mousePos = sf::Mouse::getPosition(window);
  auto mousePosWorld = window.mapPixelToCoords(mousePos, view);

  if ((mousePosWorld.x > WIDTH || mousePosWorld.x < 0) ||
      (mousePosWorld.y > HEIGHT || mousePosWorld.y < 0))
    return;

  position = {mousePosWorld.x - shapeRadius, mousePosWorld.y - shapeRadius};
  circleShape.setPosition(position);
};

void Player::render(sf::RenderWindow &window) { window.draw(circleShape); };
