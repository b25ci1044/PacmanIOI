#include "globals.h"

void drawPortal(sf::RenderWindow &window, sf::Vector2f center, float animTime)
{
  float pulse_value = 0.85f + 0.15f * std::sin(animTime * 4.0f);



  float ring1_radius = 13.0f * pulse_value;
  float ring1_thickness = 3.5f;
  float ring1_speed = 1.0f;
  sf::Color ring1_colorA(0, 220, 255);
  sf::Color ring1_colorB(180, 0, 255);

  float t1 = (std::sin(animTime * ring1_speed * 3.0f) + 1.0f) / 2.0f;
  int r1 = (int)(ring1_colorA.r * (1 - t1) + ring1_colorB.r * t1);
  int g1 = (int)(ring1_colorA.g * (1 - t1) + ring1_colorB.g * t1);
  int b1 = (int)(ring1_colorA.b * (1 - t1) + ring1_colorB.b * t1);
  sf::Color col1((uint8_t)r1, (uint8_t)g1, (uint8_t)b1);
  window.draw(createThickArc(center, ring1_radius, ring1_thickness, 0.0f, 360.0f, col1));

  float ring2_radius = 9.0f * pulse_value;
  float ring2_thickness = 2.5f;
  float ring2_speed = -1.5f;
  sf::Color ring2_colorA(180, 0, 255);
  sf::Color ring2_colorB(0, 255, 180);

  float t2 = (std::sin(animTime * ring2_speed * 3.0f) + 1.0f) / 2.0f;
  int r2 = (int)(ring2_colorA.r * (1 - t2) + ring2_colorB.r * t2);
  int g2 = (int)(ring2_colorA.g * (1 - t2) + ring2_colorB.g * t2);
  int b2_val = (int)(ring2_colorA.b * (1 - t2) + ring2_colorB.b * t2);
  sf::Color col2((uint8_t)r2, (uint8_t)g2, (uint8_t)b2_val);
  window.draw(createThickArc(center, ring2_radius, ring2_thickness, 0.0f, 360.0f, col2));

  float ring3_radius = 5.0f * pulse_value;
  float ring3_thickness = 2.0f;
  float ring3_speed = 2.5f;
  sf::Color ring3_colorA(0, 255, 180);
  sf::Color ring3_colorB(0, 180, 255);

  float t3 = (std::sin(animTime * ring3_speed * 3.0f) + 1.0f) / 2.0f;
  int r3 = (int)(ring3_colorA.r * (1 - t3) + ring3_colorB.r * t3);
  int g3 = (int)(ring3_colorA.g * (1 - t3) + ring3_colorB.g * t3);
  int b3 = (int)(ring3_colorA.b * (1 - t3) + ring3_colorB.b * t3);
  sf::Color col3((uint8_t)r3, (uint8_t)g3, (uint8_t)b3);
  window.draw(createThickArc(center, ring3_radius, ring3_thickness, 0.0f, 360.0f, col3));

  float dotR_temp = 3.0f * pulse_value;
  sf::CircleShape center_dot(dotR_temp);
  center_dot.setOrigin(sf::Vector2f(dotR_temp, dotR_temp));
  center_dot.setPosition(center);
  float brightness_temp = (std::sin(animTime * 6.0f) + 1.0f) / 2.0f;
  int dot_r = (int)(100 + 155 * brightness_temp);
  int dot_g = (int)(200 + 55 * brightness_temp);
  center_dot.setFillColor(sf::Color((uint8_t)dot_r, (uint8_t)dot_g, 255));
  window.draw(center_dot);
}

void drawArena(sf::RenderWindow &window, float uiOffset, float animTime)
{
  unsigned map_width_var = (unsigned)baseMap[0].size();
  unsigned map_height_var = (unsigned)baseMap.size();

  sf::Color wall_color_temp(33, 33, 255);

  unsigned row = 0;
  while (row < map_height_var)
  {
    unsigned col = 0;
    while (col < map_width_var)
    {
      char current_tile = baseMap[row][col];
      float xp = col * TILE_SIZE;
      float yp = row * TILE_SIZE + uiOffset;

      if (current_tile == '#')
      {
        float line_thickness = 2.f;
        float corner_radius = 8.f;

        bool open_top = false;
        if (row > 0) {
          if (baseMap[row - 1][col] != '#') {
            open_top = true;
          }
        }

        bool open_bottom = false;
        if (row < map_height_var - 1) {
          if (baseMap[row + 1][col] != '#') {
            open_bottom = true;
          }
        }

        bool open_left = false;
        if (col > 0) {
          if (baseMap[row][col - 1] != '#') {
            open_left = true;
          }
        }

        bool open_right = false;
        if (col < map_width_var - 1) {
          if (baseMap[row][col + 1] != '#') {
            open_right = true;
          }
        }

        if (open_top == true)
        {
          float left_offset = 0.f;
          if (open_left == true) {
            left_offset = corner_radius;
          }
          float right_offset = 0.f;
          if (open_right == true) {
            right_offset = corner_radius;
          }
          sf::RectangleShape top_line(sf::Vector2f(TILE_SIZE - left_offset - right_offset, line_thickness));
          top_line.setPosition(sf::Vector2f(xp + left_offset, yp));
          top_line.setFillColor(wall_color_temp);
          window.draw(top_line);
        }
        if (open_bottom == true)
        {
          float left_offset = 0.f;
          if (open_left == true) {
            left_offset = corner_radius;
          }
          float right_offset = 0.f;
          if (open_right == true) {
            right_offset = corner_radius;
          }
          sf::RectangleShape bottom_line(sf::Vector2f(TILE_SIZE - left_offset - right_offset, line_thickness));
          bottom_line.setPosition(sf::Vector2f(xp + left_offset, yp + TILE_SIZE - line_thickness));
          bottom_line.setFillColor(wall_color_temp);
          window.draw(bottom_line);
        }
        if (open_left == true)
        {
          float top_offset = 0.f;
          if (open_top == true) {
            top_offset = corner_radius;
          }
          float bottom_offset = 0.f;
          if (open_bottom == true) {
            bottom_offset = corner_radius;
          }
          sf::RectangleShape left_line(sf::Vector2f(line_thickness, TILE_SIZE - top_offset - bottom_offset));
          left_line.setPosition(sf::Vector2f(xp, yp + top_offset));
          left_line.setFillColor(wall_color_temp);
          window.draw(left_line);
        }
        if (open_right == true)
        {
          float top_offset = 0.f;
          if (open_top == true) {
            top_offset = corner_radius;
          }
          float bottom_offset = 0.f;
          if (open_bottom == true) {
            bottom_offset = corner_radius;
          }
          sf::RectangleShape right_line(sf::Vector2f(line_thickness, TILE_SIZE - top_offset - bottom_offset));
          right_line.setPosition(sf::Vector2f(xp + TILE_SIZE - line_thickness, yp + top_offset));
          right_line.setFillColor(wall_color_temp);
          window.draw(right_line);
        }

        if (open_top == true && open_left == true) {
          window.draw(createThickArc(sf::Vector2f(xp + corner_radius, yp + corner_radius), corner_radius, line_thickness, 180, 270, wall_color_temp));
        }
        if (open_top == true && open_right == true) {
          window.draw(createThickArc(sf::Vector2f(xp + TILE_SIZE - corner_radius, yp + corner_radius), corner_radius, line_thickness, 270, 360, wall_color_temp));
        }
        if (open_bottom == true && open_left == true) {
          window.draw(createThickArc(sf::Vector2f(xp + corner_radius, yp + TILE_SIZE - corner_radius), corner_radius, line_thickness, 90, 180, wall_color_temp));
        }
        if (open_bottom == true && open_right == true) {
          window.draw(createThickArc(sf::Vector2f(xp + TILE_SIZE - corner_radius, yp + TILE_SIZE - corner_radius), corner_radius, line_thickness, 0, 90, wall_color_temp));
        }
      }
      else if (current_tile == '-')
      {
        sf::RectangleShape door_shape(sf::Vector2f(TILE_SIZE, TILE_SIZE / 4.f));
        door_shape.setPosition(sf::Vector2f(xp, yp + TILE_SIZE / 2.f));
        door_shape.setFillColor(sf::Color(255, 182, 255));
        window.draw(door_shape);
      }

      col = col + 1;
    }
    row = row + 1;
  }

  float portal_y_position = 14 * TILE_SIZE + TILE_SIZE / 2 + uiOffset;
  drawPortal(window, sf::Vector2f(TILE_SIZE / 2.f, portal_y_position), animTime);
  drawPortal(window, sf::Vector2f((map_width_var - 1) * TILE_SIZE + TILE_SIZE / 2.f, portal_y_position), animTime);
}
