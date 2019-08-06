#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include "canvas.h"
#include "constants.h"

template<typename Callback>
void paintOntoCanvas(sf::RenderWindow& window, Callback callback) {
    for (int y = -5; y <= 5; y++) {
        for (int x = -5; x <= 5; x++) {
            callback(
                sf::Mouse::getPosition(window).x + x,
                sf::Mouse::getPosition(window).y + y 
            );
        }
    }
}

int main() {
    sf::RenderWindow window({WIDTH, HEIGHT}, "Fake Paint", sf::Style::Close);
    window.setFramerateLimit(60);

    Canvas canvas(WIDTH, HEIGHT);

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
        //Input
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            paintOntoCanvas(window, [&canvas](unsigned x, unsigned y) {
                canvas.changePixel(x, y, sf::Color::Black);
            }); 
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            paintOntoCanvas(window, [&canvas](unsigned x, unsigned y) {
                canvas.erasePixel(x, y);
            });
        }

        //Update
        canvas.update();

        //Render
        window.clear();
        canvas.render(window);
        window.display();
    }
}