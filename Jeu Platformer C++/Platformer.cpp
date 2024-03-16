#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Le jeu de la mort qui tue", sf::Style::Fullscreen);
    sf::Texture t;
    t.loadFromFile("imgs/image.png");
    sf::Sprite s(t);
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape Player(sf::Vector2f(100,100));
    sf::RectangleShape rectangle(sf::Vector2f(300, 20)); // circle with radius 50
    sf::RectangleShape rectangle2(sf::Vector2f(300, 20)); // circle with radius 50
    rectangle.setFillColor(sf::Color::Red); // fill color
    rectangle2.setFillColor(sf::Color::Red); // fill color
    Player.setPosition(375, 275);
    rectangle.setPosition(200, 600); // position in the middle of the window
    rectangle2.setPosition(1400, 600); // position in the middle of the window

    bool lastMoveRight = true; // true if the last move was to the right, false if it was to the left

    sf::Clock standbyClock;
    int currentFrame = 0;
    int numberOfFramesstandby = 5;
    sf::Texture standbyTexture [5];
    // load the textures 
    standbyTexture[0].loadFromFile("imgs/Character/sb1.png");
    standbyTexture[1].loadFromFile("imgs/Character/sb2.png");
    standbyTexture[2].loadFromFile("imgs/Character/sb3.png");
    standbyTexture[3].loadFromFile("imgs/Character/sb4.png");
    standbyTexture[4].loadFromFile("imgs/Character/sb5.png");

    sf::Clock standbyiClock;
    int numberOfFramesstandbyi = 5;
    sf::Texture standbyiTexture [5];
    // load the textures
    standbyiTexture[0].loadFromFile("imgs/Character/sbi1.png");
    standbyiTexture[1].loadFromFile("imgs/Character/sbi2.png");
    standbyiTexture[2].loadFromFile("imgs/Character/sbi3.png");
    standbyiTexture[3].loadFromFile("imgs/Character/sbi4.png");
    standbyiTexture[4].loadFromFile("imgs/Character/sbi5.png");

    sf::Clock leftwalkClock;
    int numberOfFramesleftwalk = 7;
    sf::Texture leftwalkTexture [7];
    // load the textures
    leftwalkTexture[0].loadFromFile("imgs/Character/move1.png");
    leftwalkTexture[1].loadFromFile("imgs/Character/move2.png");
    leftwalkTexture[2].loadFromFile("imgs/Character/move3.png");
    leftwalkTexture[3].loadFromFile("imgs/Character/move4.png");
    leftwalkTexture[4].loadFromFile("imgs/Character/move5.png");
    leftwalkTexture[5].loadFromFile("imgs/Character/move6.png");
    leftwalkTexture[6].loadFromFile("imgs/Character/move7.png");

    sf::Clock rightwalkClock;
    int numberOfFramesrightwalk = 8;
    sf::Texture rightwalkTexture [8];
    // load the textures
    rightwalkTexture[0].loadFromFile("imgs/Character/movei1.png");
    rightwalkTexture[1].loadFromFile("imgs/Character/movei2.png");
    rightwalkTexture[2].loadFromFile("imgs/Character/movei3.png");
    rightwalkTexture[3].loadFromFile("imgs/Character/movei4.png");
    rightwalkTexture[4].loadFromFile("imgs/Character/movei5.png");
    rightwalkTexture[5].loadFromFile("imgs/Character/movei6.png");
    rightwalkTexture[6].loadFromFile("imgs/Character/movei7.png");
    rightwalkTexture[7].loadFromFile("imgs/Character/movei8.png");

    float gravity = 0.3f; // gravity force (decreased for longer jumps)
    float velocity = 0.0f; // initial vertical velocity
    int jumps = 0; // number of jumps since the last ground contact
    bool wasZPressed = false; // was the space key pressed during the last iteration?

    bool isDashing = false;
    float dashDistance = 0.0f;
    float dashDirection = 0.0f;
    sf::Clock dashClock;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // animation

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            // Handle D key press
            lastMoveRight = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            // Handle Q key press
            lastMoveRight = false;
        }

        sf::Time timeSinceLastStandbyFrame = standbyClock.getElapsedTime();
        if (timeSinceLastStandbyFrame.asSeconds() >= 1.0f) { // 1 second cooldown
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && 
                !sf::Keyboard::isKeyPressed(sf::Keyboard::E) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                currentFrame = (currentFrame + 1) % (lastMoveRight ? numberOfFramesstandby : numberOfFramesstandbyi);
                Player.setTexture(lastMoveRight ? &standbyiTexture[currentFrame] : &standbyTexture[currentFrame]);
                standbyClock.restart();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            currentFrame = (currentFrame + 5) % numberOfFramesleftwalk;
            Player.setTexture(&leftwalkTexture[currentFrame]);
            standbyClock.restart();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            currentFrame = (currentFrame + 5) % numberOfFramesrightwalk;
            Player.setTexture(&rightwalkTexture[currentFrame]);
            standbyClock.restart();
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
        if (Player.getPosition().y + Player.getSize().y > window.getSize().y)
        {
            Player.setPosition(Player.getPosition().x, window.getSize().y - Player.getSize().y);
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

        // move the player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && Player.getPosition().x > 0)
            Player.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Player.getPosition().x + Player.getSize().x < window.getSize().x)
            Player.move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Player.getPosition().y + Player.getSize().y < window.getSize().y)
            Player.move(0, 8);

        // dash the player
        sf::Time timeSinceLastDash = dashClock.getElapsedTime();
        if (!isDashing && timeSinceLastDash.asSeconds() >= 5.0f) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Player.getPosition().x > 0) {
                isDashing = true;
                dashDirection = -80.0f;
                dashClock.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && Player.getPosition().x + Player.getSize().x < window.getSize().x) {
                isDashing = true;
                dashDirection = 80.0f;
                dashClock.restart();
            }
        }

        if (isDashing) {
            if (dashDistance < 500.0f) {
                if ((dashDirection < 0 && Player.getPosition().x > 0) || 
                    (dashDirection > 0 && Player.getPosition().x + Player.getSize().x < window.getSize().x)) {
                    Player.move(dashDirection, 0);
                    dashDistance += std::abs(dashDirection);
                } else {
                    isDashing = false;
                    dashDistance = 0.0f;
                }
            } else {
                isDashing = false;
                dashDistance = 0.0f;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(s);
        window.draw(Player);
        window.draw(rectangle);
        window.draw(rectangle2);
        window.display();
    }

    return 0;
}