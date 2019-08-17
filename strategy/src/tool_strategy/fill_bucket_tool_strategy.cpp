#include "tool_type_strategy.h"

#include "../canvas.h"

namespace {
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
}

void FillBucketToolStrategy::handleMouseDown(sf::Event e, Canvas& canvas, const Colours& colours) {
    float x = e.mouseButton.x;
    float y = e.mouseButton.y;
    const auto target = canvas.getPixelColour(x, y);
    if(target) {
        flood(canvas, colours.primaryColour, *target, x, y, 0);
    }
}

void FillBucketToolStrategy::handleMouseUp(sf::Event e, Canvas& canvas, const Colours& colours) { }

void FillBucketToolStrategy::handleMouseMove(sf::Event e, Canvas& canvas, const Colours& colours) { }

