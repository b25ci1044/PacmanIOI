#pragma once

#include "globals.h"
#include <iostream>

inline std::vector<sf::Vector2f> spawnOrbs(float uiOffset)
{
  std::vector<sf::Vector2f> orbs_list;

  unsigned row_counter = 0;
  while (row_counter < baseMap.size())
  {
    unsigned col_counter = 0;
    while (col_counter < baseMap[row_counter].size())
    {
      char tile_char = baseMap[row_counter][col_counter];

      bool is_valid_spot = true;
      if (tile_char == '#') {
        is_valid_spot = false;
      }
      if (tile_char == 'x') {
        is_valid_spot = false;
      }
      if (tile_char == '-') {
        is_valid_spot = false;
      }

      if (is_valid_spot == true)
      {
        sf::Vector2f orb_position;
        orb_position.x = col_counter * TILE_SIZE + TILE_SIZE / 2;
        orb_position.y = row_counter * TILE_SIZE + TILE_SIZE / 2 + uiOffset;
        orbs_list.push_back(orb_position);
      }

      col_counter = col_counter + 1;
    }
    row_counter = row_counter + 1;
  }


  return orbs_list;
}

inline void drawOrbs(sf::RenderWindow &window,
                     const std::vector<sf::Vector2f> &orbs)
{
  sf::CircleShape orb_circle_shape(3.f);
  orb_circle_shape.setFillColor(sf::Color::White);
  orb_circle_shape.setOrigin({3, 3});

  int i = 0;
  while (i < (int)orbs.size())
  {
    orb_circle_shape.setPosition(orbs[i]);
    window.draw(orb_circle_shape);

    i = i + 1;
  }
}

inline void drawHeart(sf::RenderWindow &window, sf::Vector2f pos, float size)
{
  sf::Color heart_color(220, 40, 80);

  sf::CircleShape left_lobe(size * 0.55f);
  left_lobe.setFillColor(heart_color);
  left_lobe.setOrigin({size * 0.55f, size * 0.55f});

  left_lobe.setPosition(pos + sf::Vector2f(-size * 0.28f, -size * 0.25f));
  window.draw(left_lobe);

  left_lobe.setPosition(pos + sf::Vector2f(size * 0.28f, -size * 0.25f));
  window.draw(left_lobe);

  sf::VertexArray heart_triangle(sf::PrimitiveType::Triangles, 3);
  heart_triangle[0] = sf::Vertex{pos + sf::Vector2f(-size * 0.85f, -size * 0.1f), heart_color};
  heart_triangle[1] = sf::Vertex{pos + sf::Vector2f(size * 0.85f, -size * 0.1f), heart_color};
  heart_triangle[2] = sf::Vertex{pos + sf::Vector2f(0.0f, size * 0.85f), heart_color};
  window.draw(heart_triangle);
}

inline void drawScore(sf::RenderWindow &window, const sf::Font &font,
                      int score, int lives = -1)
{
  sf::Text score_text(font, "Score: " + std::to_string(score), 24);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition({10, 5});
  window.draw(score_text);

  if (lives >= 0)
  {
    float right_side = (float)window.getSize().x;

    int heart_counter = 0;
    while (heart_counter < lives)
    {
      float heart_x = right_side - 22.f - (heart_counter * 22.f);
      drawHeart(window, {heart_x, 20.f}, 8.f);

      heart_counter = heart_counter + 1;
    }
  }
}

inline bool collectOrbs(std::vector<sf::Vector2f> &orbs,
                        const sf::Vector2f &pacPos, int &score)
{
  int number_of_orbs_before = (int)orbs.size();


  int index = (int)orbs.size() - 1;
  while (index >= 0)
  {
    float distance_temp = calcDist(pacPos, orbs[index]);

    if (distance_temp < TILE_SIZE / 2)
    {
      score = score + 1;

      orbs.erase(orbs.begin() + index);
    }

    index = index - 1;
  }

  int number_of_orbs_after = (int)orbs.size();
  if (number_of_orbs_after < number_of_orbs_before) {
    return true;
  }
  return false;
}
