#pragma once
#include "ghosts_com.h"
#include <iostream>

class TrackerGhost : public Ghost {
public:
  TrackerGhost(sf::Color ghostColor) : Ghost(ghostColor) {}

protected:
  sf::Vector2f getSpecificTargetTile(sf::Vector2f pacmanWorldPos,
                                     sf::Vector2f pacmanTilePos,
                                     Direction pacmanDir,
                                     sf::Vector2f scatterTile,
                                     float tileSize) override {
    return pacmanTilePos;
  }
};

class WandererGhost : public Ghost {
public:
  WandererGhost(sf::Color ghostColor) : Ghost(ghostColor) {}

protected:
  sf::Vector2f getSpecificTargetTile(sf::Vector2f pacmanWorldPos,
                                     sf::Vector2f pacmanTilePos,
                                     Direction pacmanDir,
                                     sf::Vector2f scatterTile,
                                     float tileSize) override {
    float distance_to_pacman = calcDist(this->pos, pacmanWorldPos);
    float threshold_distance = tileSize * 8.0f;


    if (distance_to_pacman > threshold_distance) {
      return pacmanTilePos;
    } else {
      return scatterTile;
    }
  }
};

class PredictorGhost : public Ghost {
public:
  PredictorGhost(sf::Color ghostColor) : Ghost(ghostColor) { ghostID = 1; }

protected:
  sf::Vector2f getSpecificTargetTile(sf::Vector2f pacmanWorldPos,
                                     sf::Vector2f pacmanTilePos,
                                     Direction pacmanDir,
                                     sf::Vector2f scatterTile,
                                     float tileSize) override {
    sf::Vector2f movement_direction = getDirectionVector(pacmanDir);

    sf::Vector2f target_position;
    target_position.x = pacmanTilePos.x + (movement_direction.x * 4);
    target_position.y = pacmanTilePos.y + (movement_direction.y * 4);

    return target_position;
  }
};

class AmbusherGhost : public Ghost {
public:
  AmbusherGhost(sf::Color ghostColor) : Ghost(ghostColor) { ghostID = 3; }

  float getSpeedMultiplier() const override { return 1.2f; }

protected:
  sf::Vector2f getSpecificTargetTile(sf::Vector2f pacmanWorldPos,
                                     sf::Vector2f pacmanTilePos,
                                     Direction pacmanDir,
                                     sf::Vector2f scatterTile,
                                     float tileSize) override {
    sf::Vector2f movement_direction = getDirectionVector(pacmanDir);

    sf::Vector2f target_position;
    target_position.x = pacmanTilePos.x - (movement_direction.x * 2);
    target_position.y = pacmanTilePos.y - (movement_direction.y * 2);

    return target_position;
  }
};



inline std::vector<std::shared_ptr<Ghost>> initializeGhosts(float uiOffset) {
  std::vector<std::shared_ptr<Ghost>> ghosts_list;

  sf::Vector2f spawn_point_0;
  spawn_point_0.x = 12 * TILE_SIZE + TILE_SIZE / 2;
  spawn_point_0.y = 13 * TILE_SIZE + TILE_SIZE / 2 + uiOffset;

  sf::Vector2f spawn_point_1;
  spawn_point_1.x = 13 * TILE_SIZE + TILE_SIZE / 2;
  spawn_point_1.y = 13 * TILE_SIZE + TILE_SIZE / 2 + uiOffset;

  sf::Vector2f spawn_point_2;
  spawn_point_2.x = 14 * TILE_SIZE + TILE_SIZE / 2;
  spawn_point_2.y = 13 * TILE_SIZE + TILE_SIZE / 2 + uiOffset;

  sf::Vector2f spawn_point_3;
  spawn_point_3.x = 15 * TILE_SIZE + TILE_SIZE / 2;
  spawn_point_3.y = 13 * TILE_SIZE + TILE_SIZE / 2 + uiOffset;

  std::shared_ptr<Ghost> tracker_ghost = std::make_shared<TrackerGhost>(sf::Color::Red);
  tracker_ghost->ghostID = 0;
  tracker_ghost->pos = spawn_point_0;
  tracker_ghost->currentDir = Direction::Left;
  ghosts_list.push_back(tracker_ghost);

  std::shared_ptr<Ghost> predictor_ghost = std::make_shared<PredictorGhost>(sf::Color(255, 184, 255));
  predictor_ghost->ghostID = 1;
  predictor_ghost->pos = spawn_point_1;
  predictor_ghost->currentDir = Direction::Left;
  ghosts_list.push_back(predictor_ghost);

  std::shared_ptr<Ghost> wanderer_ghost = std::make_shared<WandererGhost>(sf::Color::Cyan);
  wanderer_ghost->ghostID = 2;
  wanderer_ghost->pos = spawn_point_2;
  wanderer_ghost->currentDir = Direction::Left;
  ghosts_list.push_back(wanderer_ghost);

  std::shared_ptr<Ghost> ambusher_ghost = std::make_shared<AmbusherGhost>(sf::Color(255, 184, 82));
  ambusher_ghost->ghostID = 3;
  ambusher_ghost->pos = spawn_point_3;
  ambusher_ghost->currentDir = Direction::Left;
  ghosts_list.push_back(ambusher_ghost);


  return ghosts_list;
}
