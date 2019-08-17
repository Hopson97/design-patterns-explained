#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>

class Canvas;

struct Colours {
	sf::Color primaryColour = sf::Color::Black;
	sf::Color secondaryColour = sf::Color::Black;
};


class ToolTypeStrategy {
	public:
		virtual void handleMouseDown(sf::Event e, Canvas& canvas, const Colours& colours) = 0;
		virtual void handleMouseUp(sf::Event e, Canvas& canvas, const Colours& colours) = 0;
		virtual void handleMouseMove(sf::Event e, Canvas& canvas, const Colours& colours) = 0;

		virtual void renderPreview(sf::RenderWindow& window) {};
};


class PaintBrushStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Colours& colours) override;
};

class FillBucketToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Colours& colours) override;
};

class SprayCanToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Colours& colours) override;
};

class PencilToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Colours& colours) override;
};

class LineToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Colours& colours) override;

		void renderPreview(sf::RenderWindow& window) override;
};

class SquareToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Colours& colours) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Colours& colours) override;

		void renderPreview(sf::RenderWindow& window) override;
};
