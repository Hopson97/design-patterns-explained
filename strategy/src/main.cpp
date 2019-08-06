#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include <cmath>

#include "canvas.h"
#include "constants.h"

template<typename Callback>
void paintOntoCanvas(sf::RenderWindow& window, Callback callback) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;
    int radius = 7;
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            int actualX = mouseX + x;
            int actualY = mouseY + y;

            int dx = std::abs(mouseX - actualX);
            int dy = std::abs(mouseY - actualY);

            if(std::sqrt(dx * dx + dy * dy) > radius) {
                continue;
            }

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