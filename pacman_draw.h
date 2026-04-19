#pragma once

#include "globals.h"
#include <iostream>

inline void drawPacman(sf::RenderWindow &window, sf::Vector2f pos,
                       sf::Color color, Direction dir, float animTime) {
  float pacman_radius = TILE_SIZE / 2.0f * 0.8f;

  float temp_sin_value = std::sin(animTime * 15.0f);
  if (temp_sin_value < 0) {
    temp_sin_value = temp_sin_value * -1;
  }
  float mouth_angle_degrees = temp_sin_value * 70.0f;

  float start_angle_temp = 0;
  if (dir == Direction::Down) {
    start_angle_temp = 90;
  }
  else if (dir == Direction::Left) {
    start_angle_temp = 180;
  }
  else if (dir == Direction::Up) {
    start_angle_temp = 270;
  }


  float half_mouth = mouth_angle_degrees / 2.0f;

  int total_triangles = 30;

  sf::VertexArray pacman_shape(sf::PrimitiveType::Triangles, total_triangles * 3);

  int count = 0;
  while (count < total_triangles) {
    float angle_1 = (start_angle_temp + half_mouth + (360.0f - mouth_angle_degrees) * (count / (float)total_triangles)) *
               3.14159f / 180.f;
    float angle_2 = (start_angle_temp + half_mouth + (360.0f - mouth_angle_degrees) * ((count + 1) / (float)total_triangles)) *
        3.14159f / 180.f;

    pacman_shape[count * 3 + 0] = sf::Vertex{pos, color};

    sf::Vector2f edge_point_1;
    edge_point_1.x = pos.x + std::cos(angle_1) * pacman_radius;
    edge_point_1.y = pos.y + std::sin(angle_1) * pacman_radius;
    pacman_shape[count * 3 + 1] = sf::Vertex{edge_point_1, color};

    sf::Vector2f edge_point_2;
    edge_point_2.x = pos.x + std::cos(angle_2) * pacman_radius;
    edge_point_2.y = pos.y + std::sin(angle_2) * pacman_radius;
    pacman_shape[count * 3 + 2] = sf::Vertex{edge_point_2, color};

    count = count + 1;
  }

  window.draw(pacman_shape);
}
