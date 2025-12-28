#ifndef DEBUGUI_HPP
#define DEBUGUI_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

struct DebugUI {
  sf::Font font;
  sf::Text text{font};
  double lastTextUpdateElapsedMs = 0;

  DebugUI();

  void update(double dt);
  void render(sf::RenderWindow &window);
};

#endif // DEBUGUI_HPP
