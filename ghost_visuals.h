#pragma once

#include "ghost_direction.h"
#include <iostream>

inline void drawGhostFace(sf::RenderWindow &window, sf::Vector2f pos,
                           Direction dir, int mood)
{

    sf::Vector2f look_direction_temp;
    look_direction_temp.x = 0;
    look_direction_temp.y = 0;

    if (dir == Direction::Left) {
        look_direction_temp.x = -1.5f;
    }
    else if (dir == Direction::Right) {
        look_direction_temp.x = 1.5f;
    }
    else if (dir == Direction::Up) {
        look_direction_temp.y = -1.5f;
    }
    else if (dir == Direction::Down) {
        look_direction_temp.y = 1.5f;
    }

    sf::CircleShape white_eye_circle(3.0f);
    white_eye_circle.setFillColor(sf::Color::White);
    white_eye_circle.setOrigin({1.5f, 1.5f});

    sf::CircleShape pupil_circle(1.5f);

    if (mood == 1) {
        pupil_circle.setFillColor(sf::Color::Red);
    } else {
        pupil_circle.setFillColor(sf::Color::Blue);
    }

    pupil_circle.setOrigin({0.75f, 0.75f});

    int side_counter = -1;
    while (side_counter <= 1) {

        white_eye_circle.setPosition(pos + sf::Vector2f(side_counter * 3.5f, -2.0f) + look_direction_temp);

        window.draw(white_eye_circle);

        sf::Vector2f eye_current_pos = white_eye_circle.getPosition();
        pupil_circle.setPosition(eye_current_pos + look_direction_temp);

        window.draw(pupil_circle);

        side_counter = side_counter + 2;
    }

    if (mood == 1) {
        sf::RectangleShape angry_eyebrow_shape({5.0f, 1.5f});
        angry_eyebrow_shape.setFillColor(sf::Color::Black);
        angry_eyebrow_shape.setOrigin({2.5f, 0.75f});

        angry_eyebrow_shape.setPosition(pos + sf::Vector2f(-3.5f, -5.5f));
        angry_eyebrow_shape.setRotation(sf::degrees(25));
        window.draw(angry_eyebrow_shape);

        angry_eyebrow_shape.setPosition(pos + sf::Vector2f(3.5f, -5.5f));
        angry_eyebrow_shape.setRotation(sf::degrees(-25));
        window.draw(angry_eyebrow_shape);
    }
    else if (mood == 2) {
        sf::ConvexShape red_horn(3);
        red_horn.setPoint(0, {0, 0});
        red_horn.setPoint(1, {2, 0});
        red_horn.setPoint(2, {1, -4});

        red_horn.setFillColor(sf::Color::Red);

        red_horn.setPosition(pos + sf::Vector2f(-5, -8));
        window.draw(red_horn);

        red_horn.setPosition(pos + sf::Vector2f(3, -8));
        window.draw(red_horn);
    }
}

inline void drawGhost(sf::RenderWindow &window, sf::Vector2f pos,
                      sf::Color color, Direction dir,
                      int mood, float animTime, float tileSize)
{
    drawGhostBody(window, pos, color, animTime, tileSize);

    drawGhostFace(window, pos, dir, mood);
}
