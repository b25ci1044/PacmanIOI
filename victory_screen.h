#pragma once

#include "globals.h"
#include <iostream>

class EndScreen {
public:
  const sf::Font &m_font;
  bool m_hasWon;
  int m_selectedIndex;

  EndScreen(const sf::Font &font, bool hasWon)
      : m_font(font), m_hasWon(hasWon), m_selectedIndex(0) {}

  EndChoice run(sf::RenderWindow &window) {
    sf::Text main_message_text(m_font);

    if (m_hasWon == true) {
      main_message_text.setString("Hurray, you won!");
    } else {
      main_message_text.setString("Skill issue, you lost");
    }

    main_message_text.setCharacterSize(54);
    main_message_text.setFillColor(sf::Color::Yellow);
    main_message_text.setStyle(sf::Text::Bold);

    sf::FloatRect msg_bounds = main_message_text.getLocalBounds();
    float origin_x = msg_bounds.position.x + msg_bounds.size.x / 2.f;
    float origin_y = msg_bounds.position.y + msg_bounds.size.y / 2.f;
    main_message_text.setOrigin({origin_x, origin_y});
    main_message_text.setPosition({window.getSize().x / 2.f, window.getSize().y * 0.3f});


    int NUMBER_OF_OPTIONS = 2;

    std::string option_labels[2];
    option_labels[0] = "Play Again";
    option_labels[1] = "Quit";

    sf::Text option_texts[2] = {sf::Text(m_font), sf::Text(m_font)};
    sf::RectangleShape option_boxes[2];

    int setup_counter = 0;
    while (setup_counter < NUMBER_OF_OPTIONS) {
      option_texts[setup_counter].setString(option_labels[setup_counter]);
      option_texts[setup_counter].setCharacterSize(34);
      option_texts[setup_counter].setFillColor(sf::Color::White);

      sf::FloatRect text_bounds = option_texts[setup_counter].getLocalBounds();
      float text_origin_x = text_bounds.position.x + text_bounds.size.x / 2.f;
      float text_origin_y = text_bounds.position.y + text_bounds.size.y / 2.f;
      option_texts[setup_counter].setOrigin({text_origin_x, text_origin_y});

      float y_position = window.getSize().y * 0.55f + (setup_counter * 70.f);
      option_texts[setup_counter].setPosition({window.getSize().x / 2.f, y_position});

      sf::FloatRect global_bounds = option_texts[setup_counter].getGlobalBounds();
      float box_width = global_bounds.size.x + 60.f;
      float box_height = global_bounds.size.y + 24.f;
      option_boxes[setup_counter].setSize({box_width, box_height});
      option_boxes[setup_counter].setOrigin({box_width / 2.f, box_height / 2.f});
      option_boxes[setup_counter].setPosition({window.getSize().x / 2.f, y_position});

      setup_counter = setup_counter + 1;
    }

    while (window.isOpen()) {
      while (const std::optional<sf::Event> ev = window.pollEvent()) {
        if (ev->is<sf::Event::Closed>()) {
          window.close();
          return EndChoice::Quit;
        }
        if (const auto *kp = ev->getIf<sf::Event::KeyPressed>()) {
          if (kp->code == sf::Keyboard::Key::Up) {
            m_selectedIndex = m_selectedIndex - 1;
            if (m_selectedIndex < 0) {
              m_selectedIndex = m_selectedIndex + NUMBER_OF_OPTIONS;
            }
          }
          else if (kp->code == sf::Keyboard::Key::Down) {
            m_selectedIndex = m_selectedIndex + 1;
            if (m_selectedIndex >= NUMBER_OF_OPTIONS) {
              m_selectedIndex = m_selectedIndex - NUMBER_OF_OPTIONS;
            }
          }
          else if (kp->code == sf::Keyboard::Key::Enter) {
            if (m_selectedIndex == 0) {
              return EndChoice::PlayAgain;
            }
            window.close();
            return EndChoice::Quit;
          }
        }
      }

      int draw_counter = 0;
      while (draw_counter < NUMBER_OF_OPTIONS) {
        if (draw_counter == m_selectedIndex) {
          option_boxes[draw_counter].setFillColor(sf::Color(0, 0, 210, 230));
          option_boxes[draw_counter].setOutlineThickness(2.f);
          option_boxes[draw_counter].setOutlineColor(sf::Color(120, 170, 255));
        } else {
          option_boxes[draw_counter].setFillColor(sf::Color::Transparent);
          option_boxes[draw_counter].setOutlineThickness(0.f);
        }
        draw_counter = draw_counter + 1;
      }

      window.clear(sf::Color::Black);

      window.draw(main_message_text);

      int i = 0;
      while (i < NUMBER_OF_OPTIONS) {
        window.draw(option_boxes[i]);
        window.draw(option_texts[i]);
        i = i + 1;
      }

      window.display();
    }

    return EndChoice::Quit;
  }
};
