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

class Ball {
private:
	float radius;
	float xpos;
	float ypos;
	float xVelocity;
	float yVelocity;
	sf::CircleShape shape;
public:
	Ball(float x, float y, float xvel, float yvel) {
		xpos = x;
		ypos = y;
		xvel = xvel;
		yvel = yvel;
		shape.setRadius(radius);
		shape.setPosition(xpos, ypos);
		shape.setFillColor(sf::Color::White);
	}

	void move(float windowWidth, float windowHeight) {
		xpos += xvel;

		if (xpos <= 0 || xpos + radius * 2 >= windowWidth) {
			xvel = -xvel; // Reverse horizontal direction
		}
	}
};

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout");
	Brick brick1(100, 100, 50, 20);
	Brick brick2(160, 100, 50, 20);
	Brick brick3(220, 100, 50, 20);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear();

		brick1.draw(window);
		brick2.draw(window);
		brick3.draw(window);

		window.display();
	}
	return 0;
}