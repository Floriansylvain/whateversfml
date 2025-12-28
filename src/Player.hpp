#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

class Player {
public:
  Player(float size, sf::Color color);

  sf::Vector2f position;

  void update(double dt, sf::RenderWindow &window, const sf::View &view);
  void render(sf::RenderWindow &window);

private:
  sf::CircleShape circleShape;
};

#endif // PLAYER_HPP
