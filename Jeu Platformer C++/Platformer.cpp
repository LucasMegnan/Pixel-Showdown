#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Circle", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape Player(sf::Vector2f(75,75));
    sf::RectangleShape rectangle(sf::Vector2f(300, 20)); // circle with radius 50
    sf::RectangleShape rectangle2(sf::Vector2f(300, 20)); // circle with radius 50
    Player.setFillColor(sf::Color::Green);
    rectangle.setFillColor(sf::Color::Red); // fill color
    rectangle2.setFillColor(sf::Color::Red); // fill color
    Player.setPosition(375, 275);
    rectangle.setPosition(200, 600); // position in the middle of the window
    rectangle2.setPosition(1400, 600); // position in the middle of the window

    float gravity = 0.3f; // gravity force (decreased for longer jumps)
    float velocity = 0.0f; // initial vertical velocity
    int jumps = 0; // number of jumps since the last ground contact
    bool wasZPressed = false; // was the space key pressed during the last iteration?

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // apply gravity
        float dy = velocity; // save the current velocity
        velocity += gravity;
        Player.move(0, velocity);


        if (Player.getGlobalBounds().intersects(rectangle.getGlobalBounds())){
            
            velocity = 0.0f;
            jumps = 0;
            Player.setPosition(Player.getPosition().x, rectangle.getPosition().y - Player.getSize().y / 2 * 2);   
        }

        if (Player.getGlobalBounds().intersects(rectangle2.getGlobalBounds())){
            
            velocity = 0.0f;
            jumps = 0;
            Player.setPosition(Player.getPosition().x, rectangle2.getPosition().y - Player.getSize().y / 2 * 2);   
        }

        // collision with the bottom of the screen
        if (Player.getPosition().y + 2 * Player.getSize().y > window.getSize().y)
        {
            Player.setPosition(Player.getPosition().x, window.getSize().y - 2 * Player.getSize().y);
            velocity = 0.0f;
            jumps =  0;
        }

        // jump
        bool isZPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
        if (isZPressed && !wasZPressed && jumps < 2)
        {
            velocity = jumps == 0 ? -15.0f : -15.0f; // higher jump for the second jump
            jumps++;
        }
        wasZPressed = isZPressed;

        // move the circle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && Player.getPosition().x > 0)
            Player.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Player.getPosition().x + 2 * Player.getSize().y < window.getSize().x)
            Player.move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Player.getPosition().y + 2 * Player.getSize().y < window.getSize().y)
            Player.move(0, 8);

        window.clear();
        window.draw(Player);
        window.draw(rectangle);
        window.draw(rectangle2);
        window.display();
    }

    return 0;
}