#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include <cmath>

#include "canvas.h"
#include "constants.h"

template<typename Callback>
void paintOntoCanvas(sf::RenderWindow& window, sf::Event& e, Callback callback) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;
    int radius = 4;
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
                e.mouseMove.x + x,
                e.mouseMove.y + y 
            );
        }
    }
}

int main() {
    sf::RenderWindow window({WIDTH, HEIGHT}, "Fake Paint", sf::Style::Close);
    window.setFramerateLimit(60);

    Canvas canvas(WIDTH, HEIGHT - TOOLBAR_HEIGHT, 0, TOOLBAR_HEIGHT);

    sf::RectangleShape toolbar({WIDTH, TOOLBAR_HEIGHT});
    toolbar.setPosition(0, 0);
    toolbar.setFillColor({230, 230, 230});
    toolbar.setOutlineColor(sf::Color::Black);
    toolbar.setOutlineThickness(3);

    bool mouseLeftDown = false;
    bool mouseRightDown = false;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::MouseButtonPressed:
                    switch(e.mouseButton.button) {
                        case sf::Mouse::Left:
                            mouseLeftDown = true;
                            break;

                        case sf::Mouse::Right:
                            mouseRightDown = true;
                            break;

                        default:
                            break;
                    }
                    break;

                case sf::Event::MouseButtonReleased:
                    switch(e.mouseButton.button) {
                        case sf::Mouse::Left:
                            mouseLeftDown = false;
                            break;

                        case sf::Mouse::Right:
                            mouseRightDown = false;
                            break;

                        default:
                            break;
                    }
                    break;

                case sf::Event::MouseMoved:
                    if (mouseLeftDown) {
                        paintOntoCanvas(window, e, [&canvas](unsigned x, unsigned y) {
                            canvas.changePixel(x, y, sf::Color::Black);
                        });
                    }
                    else if (mouseRightDown) {
                        paintOntoCanvas(window, e, [&canvas](unsigned x, unsigned y) {
                            canvas.erasePixel(x, y);
                        });
                    }
                    break;

                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }
        //Update
        canvas.update();

        //Render
        window.clear();
        canvas.render(window);
        window.draw(toolbar);
        window.display();
    }
}