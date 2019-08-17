#include "tool_type_strategy.h"

#include "../canvas.h"

void PencilToolStrategy::handleMouseDown(sf::Event e, Canvas& canvas, const Options& options) {
        canvas.changePixel(
        e.mouseMove.x,
        e.mouseMove.y,
        options.primaryColour
    );
}