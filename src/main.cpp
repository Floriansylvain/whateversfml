#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

constexpr int DEBUG_REFRESH_RATE_IN_MS = 250;
constexpr bool VSYNC = true;
constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;

void updateShapePosition(sf::RectangleShape &shape, sf::RenderWindow &window) {
  if (!window.hasFocus())
    return;

  auto shapeSize = shape.getSize();
  auto mousePos = sf::Mouse::getPosition(window);

  shape.setPosition(
      sf::Vector2f(mousePos.x - shapeSize.x / 2, window.getSize().y - 50));
}

std::string getDebugText(double elapsedMilliseconds) {
  if (elapsedMilliseconds <= 0)
    return "";

  return "V-SYNC: " + std::string(VSYNC ? "On" : "Off") +
         "\nFrametime: " + std::to_string(elapsedMilliseconds) +
         "\nFPS: " + std::to_string((int)(1000 / elapsedMilliseconds));
}

int main() {
  sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Whatever SFML");
  window.setVerticalSyncEnabled(VSYNC);

  sf::RectangleShape shape(sf::Vector2f(200, 25));
  shape.setFillColor(sf::Color(100, 250, 50));
  shape.setPosition(sf::Vector2f(0, HEIGHT - 50));

  sf::Clock clock;

  sf::Font font;
  if (!font.openFromFile("assets/Consolas.ttf"))
    return 0;

  sf::Text text(font);
  text.setString(getDebugText(0));

  sf::View view;
  view.setSize(sf::Vector2f(WIDTH, HEIGHT));
  view.setCenter(sf::Vector2f((float)WIDTH / 2, (float)HEIGHT / 2));

  double lastTextUpdateElapsedMs = 0;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
        return 0;
      } else if (event->is<sf::Event::Resized>()) {
        auto size = window.getSize();
        view.setSize(sf::Vector2f(size.x, size.y));
        view.setCenter(sf::Vector2f((float)size.x / 2, (float)size.y / 2));
      }
    }

    window.clear();
    updateShapePosition(shape, window);
    window.setView(view);
    window.draw(shape);
    window.draw(text);
    window.display();

    double elapsedMilliseconds =
        (double)clock.restart().asMicroseconds() / 1000;

    lastTextUpdateElapsedMs += elapsedMilliseconds;

    if (lastTextUpdateElapsedMs > DEBUG_REFRESH_RATE_IN_MS) {
      text.setString(getDebugText(elapsedMilliseconds));
      lastTextUpdateElapsedMs = 0;
    }
  }

  return 0;
}
