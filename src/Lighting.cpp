#include "Lighting.hpp"
#include <algorithm>
#include <cmath>

Lighting::Lighting() : rayVertices(sf::PrimitiveType::TriangleFan) {
  lightColor = sf::Color(255, 255, 150, 50);
};

float Lighting::intersects(Ray ray, Wall wall) {
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

sf::Vector2f Lighting::updateRay(Walls &walls, sf::Vector2f &origin,
                                 sf::Vector2f &targetPoint, float offset) {
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

void Lighting::update(double dt, sf::Vector2f &playerPosition, Walls &walls) {
  rayVertices.clear();
  hitPoints.clear();

  for (sf::Vector2 targetPoint : walls.getPoints()) {
    hitPoints.emplace_back(updateRay(walls, playerPosition, targetPoint, 0.f));
    hitPoints.emplace_back(
        updateRay(walls, playerPosition, targetPoint, 0.001f));
    hitPoints.emplace_back(
        updateRay(walls, playerPosition, targetPoint, -0.001f));
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
}

void Lighting::render(sf::RenderWindow &window) { window.draw(rayVertices); };
