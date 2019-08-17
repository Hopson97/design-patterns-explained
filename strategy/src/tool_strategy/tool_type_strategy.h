#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>

class Canvas;

struct Options {
	sf::Color primaryColour = sf::Color::Black;
	sf::Color secondaryColour = sf::Color::Black;
	
	float penRadius = 4;
};


class ToolTypeStrategy {
	public:
		virtual void handleMouseDown([[maybe_unused]]sf::Event e, [[maybe_unused]]Canvas& canvas, [[maybe_unused]]const Options& options) = 0;
		virtual void handleMouseUp([[maybe_unused]]sf::Event e, [[maybe_unused]]Canvas& canvas, [[maybe_unused]]const Options& options) {}
		virtual void handleMouseMove([[maybe_unused]]sf::Event e, [[maybe_unused]]Canvas& canvas, [[maybe_unused]]const Options& options) {}

		virtual void renderPreview([[maybe_unused]]sf::RenderWindow& window) {};
};


class PaintBrushStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Options& options) override;
};

class FillBucketToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Options& options) override;
};

class SprayCanToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Options& options) override;
};

class PencilToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Options& options) override;
};

class LineToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Options& options) override;

		void renderPreview(sf::RenderWindow& window) override;

	private:
		sf::Vector2f m_mouseDownLocation;
		sf::Vector2f m_mouseCurrentLocation;
};

class SquareToolStrategy : public ToolTypeStrategy {
	public:
		void handleMouseDown(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseUp(sf::Event e, Canvas& canvas, const Options& options) override;
		void handleMouseMove(sf::Event e, Canvas& canvas, const Options& options) override;

		void renderPreview(sf::RenderWindow& window) override;

	private:
		sf::Vector2f m_mouseDownLocation;
		sf::Vector2f m_mouseCurrentLocation;
};
