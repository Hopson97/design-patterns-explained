#include "tool_type_strategy.h"

#include "../canvas.h"

void PencilToolStrategy::handleMouseDown([[maybe_unused]] sf::Event e, [[maybe_unused]] Canvas& canvas, [[maybe_unused]] const Options& options) {

}

void PencilToolStrategy::handleMouseUp([[maybe_unused]] sf::Event e, [[maybe_unused]] Canvas& canvas, [[maybe_unused]] const Options& options) {
    
}

void PencilToolStrategy::handleMouseMove(sf::Event e, Canvas& canvas, const Options& options) {
        canvas.changePixel(
        e.mouseMove.x,
        e.mouseMove.y,
        options.primaryColour
    );
}