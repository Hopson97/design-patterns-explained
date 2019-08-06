#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include "canvas.h"
#include "constants.h"


int main() {
    sf::RenderWindow window({WIDTH, HEIGHT}, "Fake Paint", sf::Style::Close);
    window.setFramerateLimit(60);

    Canvas canvas;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }
        //INput
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int y = -5; y <= 5; y++) {
                for (int x = -5; x <= 5; x++) {
                    canvas.changePixel(
                        sf::Mouse::getPosition(window).x + x,
                        sf::Mouse::getPosition(window).y + y,
                        sf::Color::Black
                    );
                }
            }
        }

        //Update
        canvas.update();

        //Render
        window.clear();
        canvas.render(window);
        window.display();
    }
    
}