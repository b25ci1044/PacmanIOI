#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

enum class Direction { None, Up, Down, Left, Right };

inline sf::Vector2f getDirectionVector(Direction dir) {

    sf::Vector2f temp_vector_to_return;

    if (dir == Direction::Up) {
        temp_vector_to_return.x = 0;
        temp_vector_to_return.y = -1;
    }
    else if (dir == Direction::Down) {
        temp_vector_to_return.x = 0;
        temp_vector_to_return.y = 1;
    }
    else if (dir == Direction::Left) {
        temp_vector_to_return.x = -1;
        temp_vector_to_return.y = 0;
    }
    else if (dir == Direction::Right) {
        temp_vector_to_return.x = 1;
        temp_vector_to_return.y = 0;
    }
    else {
        temp_vector_to_return.x = 0;
        temp_vector_to_return.y = 0;
    }

    return temp_vector_to_return;
}

inline float calcDist(sf::Vector2f a, sf::Vector2f b) {
    float first_part_temp = a.x - b.x;
    float second_part_temp = a.y - b.y;
    return std::sqrt((first_part_temp * first_part_temp) + (second_part_temp * second_part_temp));
}

inline void drawGhostBody(sf::RenderWindow &window, sf::Vector2f pos,
                           sf::Color color, float animTime, float tileSize)
{

    float radius_of_the_ghost = tileSize / 2.0f * 0.8f;

    sf::CircleShape dome_shape(radius_of_the_ghost);
    dome_shape.setOrigin({radius_of_the_ghost, radius_of_the_ghost});
    dome_shape.setPosition(pos);
    dome_shape.setFillColor(color);

    window.draw(dome_shape);

    sf::RectangleShape body_shape({radius_of_the_ghost * 2, radius_of_the_ghost});
    body_shape.setOrigin({radius_of_the_ghost, 0});
    body_shape.setPosition(pos);
    body_shape.setFillColor(color);

    window.draw(body_shape);

    float temp_offset = std::sin(animTime * 15.0f) * 1.5f;

    sf::VertexArray triangles_for_skirt(sf::PrimitiveType::Triangles, 9);

    float width_of_triangle = (radius_of_the_ghost * 2) / 3.0f;

    int count = 0;
    while (count < 3) {
        float temp_start_x = -radius_of_the_ghost + (count * width_of_triangle);

        triangles_for_skirt[count*3+0].position = pos + sf::Vector2f(temp_start_x, radius_of_the_ghost);
        triangles_for_skirt[count*3+0].color = color;

        float extra_y = 0;
        if (count % 2 == 0) {
            extra_y = temp_offset;
        } else {
            extra_y = -temp_offset;
        }

        triangles_for_skirt[count*3+1].position = pos + sf::Vector2f(temp_start_x + width_of_triangle/2, radius_of_the_ghost + 3 + extra_y);
        triangles_for_skirt[count*3+1].color = color;

        triangles_for_skirt[count*3+2].position = pos + sf::Vector2f(temp_start_x + width_of_triangle, radius_of_the_ghost);
        triangles_for_skirt[count*3+2].color = color;

        count = count + 1;
    }

    window.draw(triangles_for_skirt);
}
