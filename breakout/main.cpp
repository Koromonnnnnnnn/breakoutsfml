#include <SFML/Graphics.hpp>

// Brick Class
class Brick {
private:
	float width;
	float height;
	float xpos;
	float ypos;
	bool Dead;
	sf::RectangleShape shape;
public:

	// Constructor initializes the brick
	Brick(float x, float y, float w, float h) {
		xpos = x;
		ypos = y;
		width = w;
		height = h;
		Dead = false;

		// Set up the shape
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(xpos, ypos);
		shape.setFillColor(sf::Color::Red);
	}

	void draw(sf::RenderWindow& window) {
		if (!Dead) {
			window.draw(shape);
		}
	}

	void killBrick() {
		Dead = true;
		shape.setFillColor(sf::Color::Transparent); // Make the brick invisible
	}
};

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout");
	Brick brick1(100, 100, 50, 20);
	Brick brick2(160, 100, 50, 20);
	Brick brick3(220, 100, 50, 20);
}