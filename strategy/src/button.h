#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

class Button {
    public:
        constexpr static unsigned BUTTON_SIZE = 32;

        Button(int x, int y, const sf::Texture& texture);

        bool isClicked(sf::Event e) const;

        void render(sf::RenderWindow& window);

    private:
        sf::RectangleShape m_button;
};