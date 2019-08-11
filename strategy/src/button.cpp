#include "button.h"

#include <iostream>

Button::Button(int x, int y, const sf::Texture& texture)
:   m_button    ({Button::BUTTON_SIZE, Button::BUTTON_SIZE})
{
    m_button.setPosition((float)x, (float)y);
    m_button.setTexture(&texture);

    m_button.setOutlineColor(sf::Color::Black);
    m_button.setOutlineThickness(2);
}

bool Button::isClicked(sf::Event e) const {
    switch (e.type) 
    {
        case sf::Event::MouseButtonPressed:
            switch (e.mouseButton.button)
            {
                case sf::Mouse::Left:
                    return m_button.getGlobalBounds().contains(
						(float)e.mouseButton.x, (float)e.mouseButton.y
                    );
                
                default:
                    break;
            }
            break;
    
        default:
            break;
    }
    return false;
}

        
void Button::render(sf::RenderWindow& window) {
    window.draw(m_button);
}