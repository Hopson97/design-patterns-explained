#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Canvas;


class ToolTypeStrategy {
	public:
		virtual void handleMouseDown(sf::Event e, Canvas& canvas) = 0;
		virtual void handleMouseUp(sf::Event e, Canvas& canvas) = 0;
		virtual void handleMouseMove(sf::Event e, Canvas& canvas) = 0;

		virtual void renderPreview(sf::RenderWindow& window) {};
};


class PaintBrushStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas) override;
		void handleMouseUp(sf::Event e, Canvas& canvas) override;
		void handleMouseMove(sf::Event e, Canvas& canvas) override;
};

class FillBucketToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas) override;
		void handleMouseUp(sf::Event e, Canvas& canvas) override;
		void handleMouseMove(sf::Event e, Canvas& canvas) override;
};

class SprayCanToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas) override;
		void handleMouseUp(sf::Event e, Canvas& canvas) override;
		void handleMouseMove(sf::Event e, Canvas& canvas) override;
};

class PencilToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas) override;
		void handleMouseUp(sf::Event e, Canvas& canvas) override;
		void handleMouseMove(sf::Event e, Canvas& canvas) override;
};

class LineToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas) override;
		void handleMouseUp(sf::Event e, Canvas& canvas) override;
		void handleMouseMove(sf::Event e, Canvas& canvas) override;

		void renderPreview(sf::RenderWindow& window) override;
};

class SquareToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas) override;
		void handleMouseUp(sf::Event e, Canvas& canvas) override;
		void handleMouseMove(sf::Event e, Canvas& canvas) override;

		void renderPreview(sf::RenderWindow& window) override;
};
