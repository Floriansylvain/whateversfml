#include "Game.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <cmath>

Game::Game()
    : gridLines(WIDTH, HEIGHT, 20.f), player(15.f, sf::Color::Green),
      rayVertices(sf::PrimitiveType::TriangleFan) {
  window.create(sf::VideoMode({WIDTH, HEIGHT}), "SFML Game");
  window.setVerticalSyncEnabled(VSYNC);

  if (!debug.font.openFromFile("assets/Consolas.ttf")) {
    window.close();
  }

  worldView.setSize({(float)WIDTH, (float)HEIGHT});
  worldView.setCenter({(float)WIDTH / 2.f, (float)HEIGHT / 2.f});

  lightColor = sf::Color(255, 255, 150, 50);
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    double dt = clock.restart().asMicroseconds() / 1000.0;
    processEvents();
    update(dt);
    render();
  }
}

void Game::onResize() {
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

  worldView.setViewport(sf::FloatRect({posX, posY}, {viewWidth, viewHeight}));
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else if (event->is<sf::Event::Resized>()) {
      onResize();
    }
  };
};

float Game::intersects(Ray ray, Wall wall) {
  auto wallVector = wall.end - wall.start;
  auto determinator =
      (ray.direction.x * wallVector.y) - (ray.direction.y * wallVector.x);

  if (determinator == 0)
    return INFINITY;

  auto rayDist = ((wall.start.x - ray.origin.x) * wallVector.y -
                  (wall.start.y - ray.origin.y) * wallVector.x);
  rayDist /= determinator;

  auto wallDist = (wall.start.x - ray.origin.x) * ray.direction.y -
                  (wall.start.y - ray.origin.y) * ray.direction.x;
  wallDist /= determinator;

  if (rayDist > 0 && wallDist >= 0 && wallDist <= 1) {
    return rayDist;
  }

  return INFINITY;
};

sf::Vector2f Game::updateRay(sf::Vector2f &origin, sf::Vector2f &targetPoint,
                             float offset) {
  auto closestDist = 1.0f;
  auto maxDist = 3000.0f;

  float angle =
      std::atan2(targetPoint.y - origin.y, targetPoint.x - origin.x) + offset;

  sf::Vector2f direction = {std::cos(angle) * maxDist,
                            std::sin(angle) * maxDist};
  Ray ray = {origin, direction};

  for (Wall wall : walls.get()) {
    auto rayDist = intersects(ray, wall);
    if (rayDist < closestDist) {
      closestDist = rayDist;
    };
  }

  return ray.origin + (ray.direction * closestDist);
}

void Game::update(double dt) {
  debug.update(dt);
  player.update(dt, window, worldView);

  // INIT/UPDATE RAYS ------------------------------------------
  sf::Vector2 playerPosition = player.position;
  rayVertices.clear();
  hitPoints.clear();

  for (sf::Vector2 targetPoint : walls.getPoints()) {
    hitPoints.emplace_back(updateRay(playerPosition, targetPoint, 0.f));
    hitPoints.emplace_back(updateRay(playerPosition, targetPoint, 0.001f));
    hitPoints.emplace_back(updateRay(playerPosition, targetPoint, -0.001f));
  }
  std::sort(hitPoints.begin(), hitPoints.end(),
            [playerPosition](sf::Vector2f a, sf::Vector2f b) -> bool {
              auto angleA =
                  atan2(playerPosition.y - a.y, playerPosition.x - a.x);
              auto angleB =
                  atan2(playerPosition.y - b.y, playerPosition.x - b.x);
              return angleA < angleB;
            });

  rayVertices.append({playerPosition, lightColor});
  for (auto hitPoint : hitPoints) {
    rayVertices.append({hitPoint, lightColor});
  }
  rayVertices.append({hitPoints[0], lightColor});
  // -----------------------------------------------------------
};

void Game::render() {
  window.clear();
  window.setView(worldView);

  gridLines.render(window);
  debug.render(window);
  player.render(window);
  walls.render(window);

  // RENDER RAYS -------
  window.draw(rayVertices);
  // -----------------

  window.display();
};
