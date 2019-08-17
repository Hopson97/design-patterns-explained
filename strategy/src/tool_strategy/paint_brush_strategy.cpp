#include "tool_type_strategy.h"

#include "../canvas.h"

#include <cmath>

void PaintBrushStrategy::handleMouseDown(sf::Event e, Canvas& canvas, const Options& options) {
    auto radius = options.penRadius;
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            int actualX = e.mouseMove.x + x;
            int actualY = e.mouseMove.y + y;

            int dx = std::abs(e.mouseMove.x - actualX);
            int dy = std::abs(e.mouseMove.y - actualY);

            if(std::sqrt(dx * dx + dy * dy) <= radius) {
                canvas.changePixel(
                    e.mouseMove.x + x,
                    e.mouseMove.y + y,
                    options.primaryColour
                );
            }
        }
    }
}