#include <SFML/Graphics.hpp>

class Brick {
private:
    float width;
    float height;
    float xpos;
    float ypos;
    bool Dead;
    sf::RectangleShape shape;
public:
    Brick(float x, float y, float w, float h) : xpos(x), ypos(y), width(w), height(h), Dead(false) {
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
        shape.setFillColor(sf::Color::Transparent);
    }

    bool isDead() const { return Dead; }
    float getX() const { return xpos; }
    float getY() const { return ypos; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
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
    Ball(float x, float y, float xvel, float yvel) : xpos(x), ypos(y), xVelocity(xvel), yVelocity(yvel), radius(10.f) {
        shape.setRadius(radius);
        shape.setPosition(xpos, ypos);
        shape.setFillColor(sf::Color::White);
    }

    void draw(sf::RenderWindow& window) {
        shape.setPosition(xpos, ypos);
        window.draw(shape);
    }

    void move(float windowWidth, float windowHeight) {
        xpos += xVelocity;
        ypos += yVelocity;

        if (xpos <= 0 || xpos + radius * 2 >= windowWidth) {
            xVelocity = -xVelocity;
        }

        if (ypos <= 0 || ypos + radius * 2 >= windowHeight) {
            yVelocity = -yVelocity;
        }
    }

    bool brickCollision(Brick& brick) {
        if (!brick.isDead() &&
            xpos + radius > brick.getX() &&
            xpos - radius < brick.getX() + brick.getWidth() &&
            ypos + radius > brick.getY() &&
            ypos - radius < brick.getY() + brick.getHeight()) {

            yVelocity = -yVelocity;
            brick.killBrick();
            return true;
        }
        return false;
    }

    bool paddleCollision(class Paddle& paddle); // Forward declaration
};

class Paddle {
private:
    float width;
    float height;
    float xpos;
    float ypos;
    float speed;
    sf::RectangleShape shape;
public:
    Paddle(float x, float y, float w, float h) : xpos(x), ypos(y), width(w), height(h), speed(0.5) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(xpos, ypos);
        shape.setFillColor(sf::Color::White);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    void moveLeft() {
        xpos -= speed;
        if (xpos < 0) xpos = 0;
        shape.setPosition(xpos, ypos);
    }

    void moveRight(float windowWidth) {
        xpos += speed;
        if (xpos + width > windowWidth) xpos = windowWidth - width;
        shape.setPosition(xpos, ypos);
    }

    void handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            moveRight(800);
        }
    }

    float getX() const { return xpos; }
    float getY() const { return ypos; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
};

// Define paddleCollision method outside of the Ball class
bool Ball::paddleCollision(Paddle& paddle) {
    if (xpos + radius > paddle.getX() &&
        xpos - radius < paddle.getX() + paddle.getWidth() &&
        ypos + radius > paddle.getY() &&
        ypos + radius < paddle.getY() + paddle.getHeight()) {

        // Reverse the vertical velocity
        yVelocity = -yVelocity;
        return true;
    }
    return false;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout");
    Brick brick1(100, 100, 50, 20);
    Brick brick2(160, 100, 50, 20);
    Brick brick3(220, 100, 50, 20);

    Ball ball(400, 300, 0.25, 0.25); 
    Paddle paddle1(340, 575, 150, 25);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        paddle1.handleInput();

        window.clear();

        ball.move(800, 600);

        brick1.draw(window);
        brick2.draw(window);
        brick3.draw(window);

        ball.draw(window);

        paddle1.draw(window);

        ball.brickCollision(brick1);
        ball.brickCollision(brick2);
        ball.brickCollision(brick3);

        // Check for ball and paddle collision
        ball.paddleCollision(paddle1);

        window.display();
    }
    return 0;
}
