#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include <functional>
#include <iostream>
#include <cmath>

#include "canvas.h"
#include "constants.h"
#include "button.h"

enum class ToolType {
    PaintBrush  = 0,
    Fill        = 1,
    Line        = 2,
    Pencil      = 3,
    SprayCan    = 4,
    Square      = 5
};

void paintOntoCanvas(sf::RenderWindow& window, sf::Event& e, std::function<void(unsigned, unsigned)> callback) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;
    int radius = 4;
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            int actualX = mouseX + x;
            int actualY = mouseY + y;

            int dx = std::abs(mouseX - actualX);
            int dy = std::abs(mouseY - actualY);

            if(std::sqrt(dx * dx + dy * dy) <= radius) {
                callback(
                    e.mouseMove.x + x,
                    e.mouseMove.y + y 
                );
            }
        }
    }
}

Button makeButton(const sf::Texture& icon) {
    static int currentX = 10;

    Button paintBrushButton(currentX, 10, icon);
    currentX += Button::BUTTON_SIZE * 2;
    return paintBrushButton;
}

int main() {
    sf::RenderWindow window({WIDTH, HEIGHT}, "Fake Paint", sf::Style::Close);
    window.setFramerateLimit(60);

    Canvas canvas(WIDTH, HEIGHT - TOOLBAR_HEIGHT, 0, TOOLBAR_HEIGHT);

    /*
        Setting up the toolbar
     */
    //Background of toolbar
    sf::RectangleShape toolbar({WIDTH, TOOLBAR_HEIGHT});
    toolbar.setPosition(0, 0);
    toolbar.setFillColor({230, 230, 230});
    toolbar.setOutlineColor(sf::Color::Black);
    toolbar.setOutlineThickness(3);

    //Toolbar button textures
    sf::Texture paintBrushIcon;
    sf::Texture fillIcon;
    sf::Texture lineIcon;
    sf::Texture pencilIcon;
    sf::Texture sprayCanIcon;
    sf::Texture squareIcon;
    paintBrushIcon.loadFromFile("res/paintbrush.png");
    fillIcon.loadFromFile("res/fill.png");
    lineIcon.loadFromFile("res/line.png");
    pencilIcon.loadFromFile("res/pencil.png");
    sprayCanIcon.loadFromFile("res/spraycan.png");
    squareIcon.loadFromFile("res/square.png");

    auto paintBrushButton = makeButton(paintBrushIcon);
    auto fillButton = makeButton(fillIcon);
    auto lineButton = makeButton(lineIcon);
    auto pencilButton = makeButton(pencilIcon);
    auto sprayButton = makeButton(sprayCanIcon);
    auto squareButton = makeButton(squareIcon);

    //Mouse state
    bool mouseLeftDown = false;
    bool mouseRightDown = false;

    ToolType currentTool = ToolType::PaintBrush;

    //Main loop
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::MouseButtonPressed:
                    switch(e.mouseButton.button) {
                        case sf::Mouse::Left:
                            if (paintBrushButton.isClicked(e)) {
                                currentTool = ToolType::PaintBrush;
                            }
                            else if (fillButton.isClicked(e)) {
                                currentTool = ToolType::Fill;
                            }
                            else if (pencilButton.isClicked(e)) {
                                currentTool = ToolType::Pencil;
                            }
                            else if (sprayButton.isClicked(e)) {
                                currentTool = ToolType::SprayCan;
                            }
                            else if (lineButton.isClicked(e)) {
                                currentTool = ToolType::Line;
                            }
                            else if (squareButton.isClicked(e)) {
                                currentTool = ToolType::Square;
                            }
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
                        switch (currentTool)
                        {
                            case ToolType::PaintBrush:
                                paintOntoCanvas(window, e, [&canvas](unsigned x, unsigned y) {
                                    canvas.changePixel(x, y, sf::Color::Black);
                                });
                                break;

                            case ToolType::Fill:
                                break;

                            case ToolType::Line:
                                break;

                            case ToolType::Pencil:
                                break;

                            case ToolType::SprayCan:
                                break;

                            case ToolType::Square:
                                break;
                        };
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
        paintBrushButton.render(window);
        fillButton.render(window);
        lineButton.render(window);
        pencilButton.render(window);
        sprayButton.render(window);
        squareButton.render(window);






        window.display();
    }
}