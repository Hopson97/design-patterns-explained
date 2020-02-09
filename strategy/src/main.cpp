#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

#include <functional>
#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <memory>

#include "canvas.h"
#include "constants.h"
#include "button.h"
#include "tool_strategy/tool_type_strategy.h"


Button makeButton(const std::string &iconPath) {
	static int currentX = 10;

	Button paintBrushButton(currentX, HEIGHT - 10 - Button::BUTTON_SIZE, iconPath);
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

    auto paintBrushButton = makeButton("res/paintbrush.png");
    auto fillButton = makeButton("res/fill.png");
    auto lineButton = makeButton("res/line.png");
    auto pencilButton = makeButton("res/pencil.png");
    auto sprayButton = makeButton("res/spraycan.png");
    auto squareButton = makeButton("res/square.png");
    auto eraserButton = makeButton("res/erase.png");

    std::unique_ptr<ToolTypeStrategy> currentTool = std::make_unique<PaintBrushStrategy>();
    Options options;

    //Mouse state
    bool mouseLeftDown = false;
    //Main loop
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::MouseButtonPressed:
                    switch(e.mouseButton.button) {
                        case sf::Mouse::Left:
                            if (paintBrushButton.isClicked(e)) {
                                currentTool = std::make_unique<PaintBrushStrategy>();
                            }
                            else if (fillButton.isClicked(e)) {
                                currentTool = std::make_unique<FillBucketToolStrategy>();
                            }
                            else if (pencilButton.isClicked(e)) {
                                currentTool = std::make_unique<PencilToolStrategy>();
                            }
                            else if (sprayButton.isClicked(e)) {
                                currentTool = std::make_unique<SprayCanToolStrategy>();
                            }
                            else if (lineButton.isClicked(e)) {
                                currentTool = std::make_unique<LineToolStrategy>();
                            }
							else if (squareButton.isClicked(e)) {
								currentTool = std::make_unique<SquareToolStrategy>();
							}
							else if (eraserButton.isClicked(e)) {
								currentTool = std::make_unique<EraserToolStrategy>();
							}
                            else {
                                currentTool->handleMouseDown(e, canvas, options);
                                mouseLeftDown = true;
                            }
                            break;

                        default:
                            break;
                    }
                    break;

                case sf::Event::MouseButtonReleased:
                    switch(e.mouseButton.button) {
                        case sf::Mouse::Left:
                            currentTool->handleMouseUp(e, canvas, options);
                            mouseLeftDown = false;
                            break;

                        default:
                            break;
                    }
                    break;

                case sf::Event::MouseMoved:
                    if (mouseLeftDown) {
                        currentTool->handleMouseMove(e, canvas, options);
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

        if(mouseLeftDown) {
            currentTool->renderPreview(window);
        }

        window.display();
    }
}