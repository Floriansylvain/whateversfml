#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>

constexpr int DEBUG_REFRESH_RATE_IN_MS = 250;
constexpr bool VSYNC = true;
constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;
constexpr float ASPECT = 16.f / 9.f;

constexpr float SPEED = 3.f;

void updateShapePosition(sf::CircleShape &shape, sf::RenderWindow &window,
                         sf::View &worldView) {
  if (!window.hasFocus())
    return;

  auto shapeRadius = shape.getRadius();
  auto mousePos = sf::Mouse::getPosition(window);
  auto mousePosWorld = window.mapPixelToCoords(mousePos, worldView);

  shape.setPosition(sf::Vector2f(mousePosWorld.x - shapeRadius,
                                 mousePosWorld.y - shapeRadius));
}

std::string getDebugText(double elapsedMilliseconds, sf::View &worldView) {
  if (elapsedMilliseconds <= 0)
    return "";

  auto viewPos = worldView.getCenter();

  return "V-SYNC: " + std::string(VSYNC ? "On" : "Off") +
         "\nFrametime: " + std::to_string(elapsedMilliseconds) +
         "\nFPS: " + std::to_string((int)(1000 / elapsedMilliseconds)) +
         "\n\nView x, y: " + std::to_string((int)viewPos.x) + ", " +
         std::to_string((int)viewPos.y);
}

void drawGrid(sf::RenderWindow &window) {
  sf::Color gray(64, 64, 64);
  sf::VertexArray lines(sf::PrimitiveType::Lines);

  for (float x = 0; x <= WIDTH; x += 20.f) {
    lines.append(sf::Vertex{{x, 0.f}, gray});
    lines.append(sf::Vertex{{x, HEIGHT}, gray});
  }

  for (float y = 0; y <= HEIGHT; y += 20.f) {
    lines.append(sf::Vertex{{0.f, y}, gray});
    lines.append(sf::Vertex{{WIDTH, y}, gray});
  }

  window.draw(lines);
}

int main() {
  sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Whatever SFML");
  window.setVerticalSyncEnabled(VSYNC);

  sf::RectangleShape worldLimit({WIDTH - 6, HEIGHT - 6});
  worldLimit.setFillColor(sf::Color::Transparent);
  worldLimit.setOutlineColor(sf::Color::Red);
  worldLimit.setOutlineThickness(3.f);
  worldLimit.setPosition({3.f, 3.f});

  sf::CircleShape shape(15.f);
  shape.setFillColor(sf::Color(100, 250, 50));
  shape.setPosition({0, HEIGHT});

  sf::Clock clock;

  sf::Font font;
  if (!font.openFromFile("assets/Consolas.ttf"))
    return 0;

  sf::Text debugUI(font);
  debugUI.setString("");

  sf::View worldView;
  worldView.setSize({WIDTH, HEIGHT});
  worldView.setCenter({(float)WIDTH / 2, (float)HEIGHT / 2});

  double lastTextUpdateElapsedMs = 0;

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
        return 0;
      } else if (event->is<sf::Event::Resized>()) {
        auto windowSize = window.getSize();
        float windowRatio =
            static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
        float viewWidth = 1.0f;
        float viewHeight = 1.0f;
        float posX = 0.0f;
        float posY = 0.0f;

        if (windowRatio > ASPECT) {
          viewWidth = ASPECT / windowRatio;
          posX = (1.0f - viewWidth) / 2.0f;
        } else {
          viewHeight = windowRatio / ASPECT;
          posY = (1.0f - viewHeight) / 2.0f;
        }

        worldView.setViewport(
            sf::FloatRect({posX, posY}, {viewWidth, viewHeight}));
      }
    }

    updateShapePosition(shape, window, worldView);

    window.clear();

    window.setView(worldView);
    window.draw(shape);
    drawGrid(window);
    // window.draw(worldLimit);
    window.draw(debugUI);

    window.display();

    double elapsedMilliseconds =
        (double)clock.restart().asMicroseconds() / 1000;

    lastTextUpdateElapsedMs += elapsedMilliseconds;

    if (lastTextUpdateElapsedMs > DEBUG_REFRESH_RATE_IN_MS) {
      debugUI.setString(getDebugText(elapsedMilliseconds, worldView));
      lastTextUpdateElapsedMs = 0;
    }
  }

  return 0;
}
