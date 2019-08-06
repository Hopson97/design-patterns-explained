#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace {
    constexpr unsigned WIDTH = 1280;
    constexpr unsigned HEIGHT = 720;
}

int main() {
    sf::RenderWindow window({WIDTH, HEIGHT}, "Fake Paint", sf::Style::Close);
    window.setFramerateLimit(60);

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
        window.clear();

        window.display();
    }
    
}