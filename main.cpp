
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>


#include "arena.cpp"
#include "globals.h"


#include "pacman_movement.h"


#include "pacman_draw.h"


#include "xp_orbs.h"


#include "powerups.h"


#include "sounds.h"


#include "ghost_visuals.h"


#include "ghosts.h"


#include "victory_screen.h"

int main() {
  unsigned map_width_variable = (unsigned)baseMap[0].size();
  unsigned map_height_variable = (unsigned)baseMap.size();
  const float ui_offset_value = 40.0f;


  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(
                              map_width_variable * (unsigned)TILE_SIZE,
                              map_height_variable * (unsigned)TILE_SIZE + (unsigned)ui_offset_value)),
                          "Pac-Man Core");

  sf::Font font("C:/Windows/Fonts/arial.ttf");

  sf::SoundBuffer blop_sound_buffer = makeBlopSound();
  sf::SoundBuffer powerup_sound_buffer = makePowerupSound();
  sf::SoundBuffer shield_sound_buffer = makeShieldSound();
  sf::SoundBuffer ghost_eat_sound_buffer = makeGhostEatSound();
  sf::SoundBuffer death_sound_buffer = makeDeathSound();
  sf::SoundBuffer win_sound_buffer = makeWinSound();

  sf::Sound blop_sound(blop_sound_buffer);
  sf::Sound powerup_sound(powerup_sound_buffer);
  sf::Sound shield_sound(shield_sound_buffer);
  sf::Sound ghost_eat_sound(ghost_eat_sound_buffer);
  sf::Sound death_sound(death_sound_buffer);
  sf::Sound win_sound(win_sound_buffer);

  Entity pacman;

  std::vector<std::shared_ptr<Ghost>> ghosts = initializeGhosts(ui_offset_value);

  int number_of_lives = 3;
  int current_score = 0;
  bool shield_is_active = false;
  float shield_timer_value = 0.f;
  bool power_is_active = false;
  float power_timer_value = 0.f;

  sf::Vector2f pacman_spawn_position;
  pacman_spawn_position.x = 14 * TILE_SIZE + TILE_SIZE / 2;
  pacman_spawn_position.y = 5 * TILE_SIZE + TILE_SIZE / 2 + ui_offset_value;

  std::vector<sf::Vector2f> orbs = spawnOrbs(ui_offset_value);

  bool keep_playing_flag = true;
  while (keep_playing_flag == true) {
    pacman.pos = pacman_spawn_position;
    pacman.currentDir = Direction::Left;
    pacman.queuedDir = Direction::Left;
    pacman.color = sf::Color::Yellow;
    current_score = 0;
    number_of_lives = 3;
    shield_is_active = false;
    shield_timer_value = 0.f;
    power_is_active = false;
    power_timer_value = 0.f;
    ghosts = initializeGhosts(ui_offset_value);
    orbs = spawnOrbs(ui_offset_value);

    std::vector<sf::Vector2f> valid_spawn_spots;
    unsigned r = 0;
    while (r < baseMap.size()) {
      unsigned c = 0;
      while (c < baseMap[r].size()) {
        bool is_good_spot = true;
        if (baseMap[r][c] == '#') { is_good_spot = false; }
        if (baseMap[r][c] == 'x') { is_good_spot = false; }
        if (baseMap[r][c] == '-') { is_good_spot = false; }

        if (is_good_spot == true) {
          sf::Vector2f spot;
          spot.x = c * TILE_SIZE + TILE_SIZE / 2;
          spot.y = r * TILE_SIZE + TILE_SIZE / 2 + ui_offset_value;
          valid_spawn_spots.push_back(spot);
        }
        c = c + 1;
      }
      r = r + 1;
    }

    std::srand((unsigned)std::time(nullptr));
    std::vector<Powerup> powerups_list;

    if (valid_spawn_spots.size() > 0) {
      int random_idx = std::rand() % (int)valid_spawn_spots.size();
      Powerup health_pu;
      health_pu.pos = valid_spawn_spots[random_idx];
      health_pu.type = PowerupType::Health;
      health_pu.active = true;
      powerups_list.push_back(health_pu);
      valid_spawn_spots.erase(valid_spawn_spots.begin() + random_idx);
    }
    if (valid_spawn_spots.size() > 0) {
      int random_idx = std::rand() % (int)valid_spawn_spots.size();
      Powerup power_pu;
      power_pu.pos = valid_spawn_spots[random_idx];
      power_pu.type = PowerupType::Power;
      power_pu.active = true;
      powerups_list.push_back(power_pu);
      valid_spawn_spots.erase(valid_spawn_spots.begin() + random_idx);
    }
    if (valid_spawn_spots.size() > 0) {
      int random_idx = std::rand() % (int)valid_spawn_spots.size();
      Powerup shield_pu;
      shield_pu.pos = valid_spawn_spots[random_idx];
      shield_pu.type = PowerupType::Shield;
      shield_pu.active = true;
      powerups_list.push_back(shield_pu);
      valid_spawn_spots.erase(valid_spawn_spots.begin() + random_idx);
    }

    sf::Clock clock;
    GameState current_game_state = GameState::Playing;
    float animation_time = 0.f;

    while (window.isOpen() && current_game_state == GameState::Playing) {
      float dt = clock.restart().asSeconds();
      if (dt > 0.1f) {
        dt = 0.1f;
      }
      animation_time = animation_time + dt;

      while (const std::optional<sf::Event> ev = window.pollEvent()) {
        if (ev->is<sf::Event::Closed>()) {
          window.close();
        }
      }

      handlePacmanInput(pacman);
      moveEntity(pacman, PACMAN_SPEED, dt, ui_offset_value, map_width_variable);

      updateGhosts(ghosts, pacman, dt, ui_offset_value, animation_time);

      bool was_hit = checkGhostCollision(pacman, ghosts, shield_is_active, power_is_active,
                                            ghost_eat_sound, death_sound, current_score);
      if (was_hit == true) {
        number_of_lives = number_of_lives - 1;
        if (number_of_lives <= 0) {
          current_game_state = GameState::GameOver;
          break;
        }
        pacman.pos = pacman_spawn_position;
      }

      int orbs_count_before = (int)orbs.size();
      collectOrbs(orbs, pacman.pos, current_score);
      int orbs_count_after = (int)orbs.size();
      if (orbs_count_after < orbs_count_before) {
        if (blop_sound.getStatus() != sf::Sound::Status::Playing) {
          blop_sound.play();
        }
      }

      if (orbs.size() == 0) {
        current_game_state = GameState::GameWon;
        win_sound.play();
        break;
      }

      int pu_index = 0;
      while (pu_index < (int)powerups_list.size()) {
        if (powerups_list[pu_index].active == false) {
          pu_index = pu_index + 1;
          continue;
        }
        float dist_to_powerup = calcDist(pacman.pos, powerups_list[pu_index].pos);
        if (dist_to_powerup < TILE_SIZE * 0.7f) {
          powerups_list[pu_index].active = false;

          if (powerups_list[pu_index].type == PowerupType::Health) {
            if (number_of_lives < 3) {
              number_of_lives = number_of_lives + 1;
            }
            powerup_sound.play();
          }
          else if (powerups_list[pu_index].type == PowerupType::Power) {
            power_is_active = true;
            power_timer_value = 8.0f;
            frightenGhosts(ghosts, 8.0f);
            powerup_sound.play();
          }
          else if (powerups_list[pu_index].type == PowerupType::Shield) {
            shield_is_active = true;
            shield_timer_value = 10.0f;
            shield_sound.play();
          }
        }
        pu_index = pu_index + 1;
      }

      if (power_is_active == true) {
        power_timer_value = power_timer_value - dt;
        if (power_timer_value <= 0.f) {
          power_is_active = false;
        }
      }
      if (shield_is_active == true) {
        shield_timer_value = shield_timer_value - dt;
        if (shield_timer_value <= 0.f) {
          shield_is_active = false;
        }
      }


      window.clear(sf::Color::Black);

      drawArena(window, ui_offset_value, animation_time);

      drawOrbs(window, orbs);

      int draw_pu_index = 0;
      while (draw_pu_index < (int)powerups_list.size()) {
        if (powerups_list[draw_pu_index].active == false) {
          draw_pu_index = draw_pu_index + 1;
          continue;
        }
        if (powerups_list[draw_pu_index].type == PowerupType::Health) {
          drawHealthPowerup(window, powerups_list[draw_pu_index].pos, animation_time);
        }
        else if (powerups_list[draw_pu_index].type == PowerupType::Power) {
          drawPowerPowerup(window, powerups_list[draw_pu_index].pos, animation_time);
        }
        else if (powerups_list[draw_pu_index].type == PowerupType::Shield) {
          drawShieldPowerup(window, powerups_list[draw_pu_index].pos, animation_time);
        }
        draw_pu_index = draw_pu_index + 1;
      }

      drawPacman(window, pacman.pos, pacman.color, pacman.currentDir, animation_time);

      drawGhostsWrapper(window, ghosts, animation_time);

      if (shield_is_active == true) {
        drawShieldAura(window, pacman.pos, animation_time);
      }

      drawScore(window, font, current_score, number_of_lives);

      window.display();
    }

    if (window.isOpen()) {
      bool did_win = false;
      if (current_game_state == GameState::GameWon) {
        did_win = true;
      }

      EndScreen end_screen(font, did_win);
      EndChoice player_choice = end_screen.run(window);

      if (player_choice == EndChoice::PlayAgain) {
        if (window.isOpen() == false) {
          window.create(sf::VideoMode(sf::Vector2u(map_width_variable * (unsigned)TILE_SIZE,
                                                   map_height_variable * (unsigned)TILE_SIZE +
                                                       (unsigned)ui_offset_value)),
                        "Pac-Man Core");
        }
        continue;
      } else {
        keep_playing_flag = false;
      }
    } else {
      keep_playing_flag = false;
    }
  }


  return 0;
}
