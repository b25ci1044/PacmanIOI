#pragma once

#include "globals.h"
#include <iostream>

inline void handlePacmanInput(Entity &pacman) {
  bool w_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
  bool up_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
  if (w_pressed == true || up_pressed == true) {
    pacman.queuedDir = Direction::Up;
  }

  bool s_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
  bool down_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
  if (s_pressed == true || down_pressed == true) {
    pacman.queuedDir = Direction::Down;
  }

  bool a_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
  bool left_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
  if (a_pressed == true || left_pressed == true) {
    pacman.queuedDir = Direction::Left;
  }

  bool d_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
  bool right_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
  if (d_pressed == true || right_pressed == true) {
    pacman.queuedDir = Direction::Right;
  }
}

inline void moveEntity(Entity &e, float spd, float dt, float uiOffset,
                       unsigned mapW) {
  int grid_x = (int)(e.pos.x / TILE_SIZE);
  int grid_y = (int)((e.pos.y - uiOffset) / TILE_SIZE);

  sf::Vector2f tile_center;
  tile_center.x = grid_x * TILE_SIZE + TILE_SIZE / 2;
  tile_center.y = grid_y * TILE_SIZE + TILE_SIZE / 2 + uiOffset;

  sf::Vector2f vector_to_center;
  vector_to_center.x = tile_center.x - e.pos.x;
  vector_to_center.y = tile_center.y - e.pos.y;

  sf::Vector2f current_dir_vector = getDirectionVector(e.currentDir);

  float dot_product_temp = vector_to_center.x * current_dir_vector.x + vector_to_center.y * current_dir_vector.y;
  bool is_moving_towards = false;
  if (dot_product_temp > 0) {
    is_moving_towards = true;
  }


  float dist_to_center = calcDist(e.pos, tile_center);

  bool should_snap = false;
  if (dist_to_center < 0.1f) {
    should_snap = true;
  }
  if (is_moving_towards == true && dist_to_center <= spd * dt) {
    should_snap = true;
  }

  if (should_snap == true) {
    e.pos = tile_center;

    sf::Vector2f queued_dir_vec = getDirectionVector(e.queuedDir);
    int next_x_queued = grid_x + (int)queued_dir_vec.x;
    int next_y_queued = grid_y + (int)queued_dir_vec.y;

    if (isWall(next_x_queued, next_y_queued) == false) {
      e.currentDir = e.queuedDir;
    }
    else {
      sf::Vector2f curr_dir_vec = getDirectionVector(e.currentDir);
      int next_x_current = grid_x + (int)curr_dir_vec.x;
      int next_y_current = grid_y + (int)curr_dir_vec.y;

      if (isWall(next_x_current, next_y_current) == true) {
        e.currentDir = Direction::None;
      }
    }

    sf::Vector2f move_vec = getDirectionVector(e.currentDir);
    e.pos.x = e.pos.x + move_vec.x * spd * dt;
    e.pos.y = e.pos.y + move_vec.y * spd * dt;
  } else {
    e.pos.x = e.pos.x + current_dir_vector.x * spd * dt;
    e.pos.y = e.pos.y + current_dir_vector.y * spd * dt;
  }

  if (e.pos.x < 0) {
    e.pos.x = e.pos.x + mapW * TILE_SIZE;
  }
  if (e.pos.x >= (float)mapW * TILE_SIZE) {
    e.pos.x = e.pos.x - mapW * TILE_SIZE;
  }
}
