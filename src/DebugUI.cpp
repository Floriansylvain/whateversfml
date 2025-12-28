#include "DebugUI.hpp"
#include "Game.hpp"
#include <string>

DebugUI::DebugUI() {}

void DebugUI::update(double dt) {
  lastTextUpdateElapsedMs += dt;

  if (lastTextUpdateElapsedMs < 250)
    return;

  std::string info = "V-SYNC: " + std::string(VSYNC ? "On" : "Off") +
                     "\nFrametime: " + std::to_string(dt) + " ms" +
                     "\nFPS: " + std::to_string(static_cast<int>(1000.0 / dt));

  text.setString(info);
  lastTextUpdateElapsedMs = 0;
}

void DebugUI::render(sf::RenderWindow &window) { window.draw(text); }
