#include <SFML/Graphics.hpp>
#include <iostream>

constexpr static unsigned WIDTH = 1280;
constexpr static unsigned HEIGHT = 720;

int main() {
    sf::RenderWindow window({WIDTH, HEIGHT}, "SFML", sf::Style::Default);
    window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

    sf::Image canvas;
    sf::Texture canvasTexture;
    sf::RectangleShape canvasRenderable;

    canvas.create(WIDTH, HEIGHT, sf::Color::White);
    canvasRenderable.setSize({WIDTH, HEIGHT});
    canvasRenderable.setTexture(&canvasTexture);

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseMoved:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        for (int y = 0; y < 10; y++) {
                            for (int x = 0; x < 10; x++) {
                                canvas.setPixel(e.mouseMove.x + x, e.mouseMove.y + y, sf::Color::Black);
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }
        window.clear();
        canvasTexture.loadFromImage(canvas);

        window.draw(canvasRenderable);

        window.display();
    }
}

