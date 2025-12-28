#include "GridLines.hpp"
#include <SFML/Graphics/Vertex.hpp>

GridLines::GridLines(float width, float height, float spacing)
    : m_lines(sf::PrimitiveType::Lines) {
  sf::Color gray(64, 64, 64);

  for (float x = 0; x <= width; x += spacing) {
    m_lines.append({{x, 0.f}, gray});
    m_lines.append({{x, height}, gray});
  }

  for (float y = 0; y <= height; y += spacing) {
    m_lines.append({{0.f, y}, gray});
    m_lines.append({{width, y}, gray});
  }
}

void GridLines::render(sf::RenderWindow &window) const { window.draw(m_lines); }
