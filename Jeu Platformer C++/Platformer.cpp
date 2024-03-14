#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Circle", sf::Style::Fullscreen);

    sf::CircleShape circle(50); // circle with radius 50
    circle.setFillColor(sf::Color::Green); // fill color
    circle.setPosition(375, 275); // position in the middle of the window

    float gravity = 0.3f; // gravity force (decreased for longer jumps)
    float velocity = 0.0f; // initial vertical velocity
    int jumps = 0; // number of jumps since the last ground contact
    bool wasSpacePressed = false; // was the space key pressed during the last iteration?

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // apply gravity
        velocity += gravity;
        circle.move(0, velocity);

        // collision with the bottom of the screen
        if (circle.getPosition().y + 2 * circle.getRadius() > window.getSize().y)
        {
            circle.setPosition(circle.getPosition().x, window.getSize().y - 2 * circle.getRadius());
            velocity = 0.0f;
            jumps = 0;
        }

        // jump
        bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (isSpacePressed && !wasSpacePressed && jumps < 2)
        {
            velocity = jumps == 0 ? -15.0f : -15.0f; // higher jump for the second jump
            jumps++;
        }
        wasSpacePressed = isSpacePressed;

        // move the circle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && circle.getPosition().x > 0)
            circle.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && circle.getPosition().x + 2 * circle.getRadius() < window.getSize().x)
            circle.move(5, 0);

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}