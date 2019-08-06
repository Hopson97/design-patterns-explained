#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

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
    canvasTexture.loadFromImage(canvas);
    canvasRenderable.setTexture(&canvasTexture);

    std::srand(std::time_t(nullptr));

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (int y = 0; y < 10; y++) {
                for (int x = 0; x < 10; x++) {
                    canvas.setPixel(
                        sf::Mouse::getPosition(window).x, 
                        sf::Mouse::getPosition(window).y, 
                        sf::Color::Black);
                }
            }
        }
        window.clear();
        canvasTexture.loadFromImage(canvas);
        
        canvas.setPixel(rand() % WIDTH, rand() % HEIGHT, sf::Color::Black);

        window.draw(canvasRenderable);

        window.display();
        std::cout << "test\n";
    }
}

