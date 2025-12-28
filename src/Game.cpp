#include "Game.hpp"

Game::Game() : gridLines(WIDTH, HEIGHT, 20.f), player(15.f, sf::Color::Green) {
  window.create(sf::VideoMode({WIDTH, HEIGHT}), "SFML Game");
  window.setVerticalSyncEnabled(VSYNC);

  if (!debug.font.openFromFile("assets/Consolas.ttf")) {
    window.close();
  }

  worldView.setSize({(float)WIDTH, (float)HEIGHT});
  worldView.setCenter({(float)WIDTH / 2.f, (float)HEIGHT / 2.f});

  walls.add({1.f, 1.f}, {WIDTH - 1.f, 1.f});
  walls.add({1.f, 1.f}, {1.f, HEIGHT - 1.f});
  walls.add({WIDTH - 1.f, 1.f}, {WIDTH - 1.f, HEIGHT - 1.f});
  walls.add({1.f, HEIGHT - 1.f}, {WIDTH - 1.f, HEIGHT - 1.f});

  walls.add({1000.f, 500.f}, {1500.f, 500.f});
  walls.add({500.f, 240.f}, {500.f, 760.f});
  walls.add({420.f, 240.f}, {420.f, 760.f});
  walls.add({420.f, 240.f}, {500.f, 240.f});
  walls.add({420.f, 760.f}, {500.f, 760.f});
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

void Game::update(double dt) {
  debug.update(dt);
  player.update(dt, window, worldView);
};

void Game::render() {
  window.clear();
  window.setView(worldView);

  gridLines.render(window);
  debug.render(window);
  player.render(window);
  walls.render(window);

  window.display();
};
