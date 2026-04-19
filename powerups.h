#pragma once

#include "globals.h"
#include <iostream>

inline void drawHealthPowerup(sf::RenderWindow &window, sf::Vector2f pos,
                              float animTime)
{
  float temp_sin = std::sin(animTime * 5.0f);
  float size_of_powerup = 5.0f * (1.0f + 0.18f * temp_sin);

  float ring_radius = size_of_powerup * 1.6f;
  sf::Color ring_color(255, 80, 80, 120);
  window.draw(createThickArc(pos, ring_radius, 2.5f, 0.0f, 360.0f, ring_color));

  sf::CircleShape heart_lobe(size_of_powerup * 0.6f);
  heart_lobe.setFillColor(sf::Color(255, 60, 100));
  heart_lobe.setOrigin({size_of_powerup * 0.6f, size_of_powerup * 0.6f});

  heart_lobe.setPosition(pos + sf::Vector2f(-size_of_powerup * 0.32f, -size_of_powerup * 0.3f));
  window.draw(heart_lobe);

  heart_lobe.setPosition(pos + sf::Vector2f(size_of_powerup * 0.32f, -size_of_powerup * 0.3f));
  window.draw(heart_lobe);

  sf::VertexArray heart_triangle(sf::PrimitiveType::Triangles, 3);
  sf::Color hc(255, 60, 100);
  heart_triangle[0] = sf::Vertex{pos + sf::Vector2f(-size_of_powerup * 0.9f, -size_of_powerup * 0.1f), hc};
  heart_triangle[1] = sf::Vertex{pos + sf::Vector2f(size_of_powerup * 0.9f, -size_of_powerup * 0.1f), hc};
  heart_triangle[2] = sf::Vertex{pos + sf::Vector2f(0.0f, size_of_powerup * 0.9f), hc};
  window.draw(heart_triangle);
}



inline void drawPowerPowerup(sf::RenderWindow &window, sf::Vector2f pos,
                             float animTime)
{
  float s = 5.5f * (1.0f + 0.15f * std::sin(animTime * 6.0f));

  window.draw(createThickArc(pos, s * 1.6f, 2.5f, 0.0f, 360.0f,
                             sf::Color(180, 80, 255, 130)));

  int star_counter = 0;
  while (star_counter < 4)
  {
    float angle_temp = animTime * 3.0f + star_counter * (2 * 3.14159f / 4.0f);
    sf::Vector2f star_pos;
    star_pos.x = pos.x + std::cos(angle_temp) * s * 0.9f;
    star_pos.y = pos.y + std::sin(angle_temp) * s * 0.9f;

    sf::VertexArray star_shape(sf::PrimitiveType::Triangles, 24);
    sf::Color star_color(255, 220, 0);
    float star_radius_temp = s * 0.38f;

    int j = 0;
    while (j < 8)
    {
      float a1 = j * 2 * 3.14159f / 8.0f;
      float a2 = (j + 1) * 2 * 3.14159f / 8.0f;

      float r1_temp = star_radius_temp;
      if (j % 2 != 0) {
        r1_temp = star_radius_temp * 0.45f;
      }
      float r2_temp = star_radius_temp;
      if ((j + 1) % 2 != 0) {
        r2_temp = star_radius_temp * 0.45f;
      }

      star_shape[j * 3 + 0] = sf::Vertex{star_pos, star_color};

      sf::Vector2f point1;
      point1.x = star_pos.x + std::cos(a1) * r1_temp;
      point1.y = star_pos.y + std::sin(a1) * r1_temp;
      star_shape[j * 3 + 1] = sf::Vertex{point1, star_color};

      sf::Vector2f point2;
      point2.x = star_pos.x + std::cos(a2) * r2_temp;
      point2.y = star_pos.y + std::sin(a2) * r2_temp;
      star_shape[j * 3 + 2] = sf::Vertex{point2, star_color};

      j = j + 1;
    }
    window.draw(star_shape);

    star_counter = star_counter + 1;
  }

  sf::CircleShape center_dot(s * 0.25f);
  center_dot.setOrigin({s * 0.25f, s * 0.25f});
  center_dot.setPosition(pos);
  center_dot.setFillColor(sf::Color(255, 220, 0, 200));
  window.draw(center_dot);
}



inline void drawShieldPowerup(sf::RenderWindow &window, sf::Vector2f pos,
                              float animTime)
{
  float s = 6.0f * (1.0f + 0.15f * std::sin(animTime * 4.5f));

  window.draw(createThickArc(pos, s * 1.6f, 2.5f, 0.0f, 360.0f,
                             sf::Color(60, 255, 120, 130)));

  sf::ConvexShape shield_shape(6);
  shield_shape.setPoint(0, {0, -s});
  shield_shape.setPoint(1, {s * 0.87f, -s * 0.5f});
  shield_shape.setPoint(2, {s * 0.87f, s * 0.5f});
  shield_shape.setPoint(3, {0, s});
  shield_shape.setPoint(4, {-s * 0.87f, s * 0.5f});
  shield_shape.setPoint(5, {-s * 0.87f, -s * 0.5f});
  shield_shape.setFillColor(sf::Color(40, 200, 80, 200));
  shield_shape.setOutlineColor(sf::Color(120, 255, 160));
  shield_shape.setOutlineThickness(1.5f);
  shield_shape.setPosition(pos);
  window.draw(shield_shape);

  sf::RectangleShape horizontal_bar({s * 0.9f, s * 0.28f});
  horizontal_bar.setOrigin({s * 0.45f, s * 0.14f});
  horizontal_bar.setPosition(pos);
  horizontal_bar.setFillColor(sf::Color(200, 255, 220));
  window.draw(horizontal_bar);

  horizontal_bar.setSize({s * 0.28f, s * 0.9f});
  horizontal_bar.setOrigin({s * 0.14f, s * 0.45f});
  window.draw(horizontal_bar);
}



inline void drawShieldAura(sf::RenderWindow &window, sf::Vector2f pos,
                           float animTime)
{
  float radius_temp = 11.0f * (1.0f + 0.12f * std::sin(animTime * 8.0f));


  window.draw(createThickArc(pos, radius_temp + 3.0f, 3.0f, 0.0f, 360.0f,
                             sf::Color(60, 255, 120, 70)));
  window.draw(createThickArc(pos, radius_temp, 2.5f, 0.0f, 360.0f,
                             sf::Color(80, 255, 140, 220)));

  int node_counter = 0;
  while (node_counter < 6)
  {
    float node_angle = animTime * 1.5f + node_counter * (2 * 3.14159f / 6.0f);

    sf::CircleShape node_circle(2.0f);
    node_circle.setOrigin({2, 2});

    sf::Vector2f node_pos;
    node_pos.x = pos.x + std::cos(node_angle) * radius_temp;
    node_pos.y = pos.y + std::sin(node_angle) * radius_temp;
    node_circle.setPosition(node_pos);

    node_circle.setFillColor(sf::Color(180, 255, 200));
    window.draw(node_circle);

    node_counter = node_counter + 1;
  }
}
