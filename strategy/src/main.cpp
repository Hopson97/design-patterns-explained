#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

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
        canvas.update();


        window.clear();

        canvas.render(window);

        window.display();
    }
    
}