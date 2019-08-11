#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include <functional>
#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>

#include "canvas.h"
#include "constants.h"
#include "button.h"

enum class ToolType {
    PaintBrush,
    Fill,
    Line,
    Pencil,
    SprayCan,
    Square,
    Eraser    
};

//////////
///
/// PAINT
///
//////////
void paintOntoCanvas(sf::Event& e, int radius, std::function<void(unsigned, unsigned)> callback) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            int actualX = e.mouseMove.x + x;
            int actualY = e.mouseMove.y + y;

            int dx = std::abs(e.mouseMove.x - actualX);
            int dy = std::abs(e.mouseMove.y - actualY);

            if(std::sqrt(dx * dx + dy * dy) <= radius) {
                callback(
                    e.mouseMove.x + x,
                    e.mouseMove.y + y 
                );
            }
        }
    }
}

//////////
///
/// FLOOD
///
//////////
void flood (Canvas& canvas, sf::Color fillColour, sf::Color targetColour, unsigned x, unsigned y, int count) {
    if (count > 50000) {
        return;
    }
    auto pxColour = canvas.getPixelColour(x, y);
    if(pxColour) {
        auto r = pxColour->r;
        auto g = pxColour->r;
        auto b = pxColour->r;
        if (r == targetColour.r && g == targetColour.g && b == targetColour.b) {
            canvas.changePixel(x, y, fillColour);
            flood(canvas, fillColour, targetColour, x + 1, y, count++);
            flood(canvas, fillColour, targetColour, x - 1, y, count++);
            flood(canvas, fillColour, targetColour, x, y + 1, count++);
            flood(canvas, fillColour, targetColour, x, y - 1, count++);
        }
    }
}

void fill(sf::Event e, Canvas& canvas, sf::Color fillColour, sf::Color targetColour) {
    flood(canvas, fillColour, targetColour, e.mouseMove.x, e.mouseMove.y, 0);
}

Button makeButton(const sf::Texture& icon) {
    static int currentX = 10;

    Button paintBrushButton(currentX, HEIGHT - 10 - Button::BUTTON_SIZE, icon);
    currentX += Button::BUTTON_SIZE * 2;
    return paintBrushButton;
}

int main() {
    sf::RenderWindow window({WIDTH, HEIGHT}, "Fake Paint", sf::Style::Close);
    window.setFramerateLimit(60);
    
    std::srand(std::time_t(0)); //I know rand() is bad, but it is fine for this

    Canvas canvas(WIDTH, HEIGHT - TOOLBAR_HEIGHT, 0, 0);

    /*
        Setting up the toolbar
     */
    //Background of toolbar
    sf::RectangleShape toolbar({WIDTH, TOOLBAR_HEIGHT});
    toolbar.setPosition(0, HEIGHT - TOOLBAR_HEIGHT);
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
    sf::Texture eraserIcon;
    paintBrushIcon.loadFromFile("res/paintbrush.png");
    fillIcon.loadFromFile("res/fill.png");
    lineIcon.loadFromFile("res/line.png");
    pencilIcon.loadFromFile("res/pencil.png");
    sprayCanIcon.loadFromFile("res/spraycan.png");
    squareIcon.loadFromFile("res/square.png");
    eraserIcon.loadFromFile("res/erase.png");

    auto paintBrushButton = makeButton(paintBrushIcon);
    auto fillButton = makeButton(fillIcon);
    auto lineButton = makeButton(lineIcon);
    auto pencilButton = makeButton(pencilIcon);
    auto sprayButton = makeButton(sprayCanIcon);
    auto squareButton = makeButton(squareIcon);
    auto eraserButton = makeButton(eraserIcon);

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
                            else if (eraserButton.isClicked(e)) {
                                currentTool = ToolType::Eraser;
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
                        switch (currentTool) {
                            case ToolType::PaintBrush:
                                paintOntoCanvas(e, 4, [&canvas](unsigned x, unsigned y) {
                                    canvas.changePixel(x, y, sf::Color::Black);
                                });
                                break;

                            case ToolType::Fill:
                                fill(e, canvas, sf::Color::Black, sf::Color::White);
                                break;

                            case ToolType::Line:
                                break;

                            case ToolType::Pencil:
                                paintOntoCanvas(e, 1, [&canvas](unsigned x, unsigned y) {
                                    canvas.changePixel(x, y, sf::Color::Black);
                                });
                                break;

                            case ToolType::SprayCan:
                                paintOntoCanvas(e, 4, [&canvas](unsigned x, unsigned y) {
                                    if (std::rand() % 100 > 50) {
                                        canvas.changePixel(x, y, sf::Color::Black);
                                    }
                                });
                                break;

                            case ToolType::Square:
                                break;

                            case ToolType::Eraser:
                                paintOntoCanvas(e, 4, [&canvas](unsigned x, unsigned y) {
                                    canvas.erasePixel(x, y);
                                });
                                break;
                        };
                    }
                    if (mouseRightDown) {

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
        eraserButton.render(window);






        window.display();
    }
}