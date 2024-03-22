#include "src/class.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pixel Showdown", sf::Style::Fullscreen);
    sf::Texture t;
    t.loadFromFile("imgs/image.png");
    sf::Sprite s(t);
    window.setVerticalSyncEnabled(true);

    Character firstPlayer;
    Character secondPlayer;

    // Creates a sprite for the 1st player
    sf::Sprite Player;
    Player.setTexture(IdleCharacterSheet[0]);
    Player.setScale(sf::Vector2f(3.0f, 3.0)); // Ajust the sprite's height if needed
    Player.setPosition(375, 275);

    //Creates a sprite for the 2nd player
    sf::Sprite Player2;
    Player2.setTexture(IdleCharacterSheet2[0]);
    Player2.setScale(sf::Vector2f(3.0f, 3.0)); // Ajust the sprite's height if needed
    Player2.setPosition(200, 200);
    

    sf::RectangleShape rectangle(sf::Vector2f(300, 20)); // circle with radius 50
    sf::RectangleShape rectangle2(sf::Vector2f(300, 20)); // circle with radius 50
    rectangle.setFillColor(sf::Color::Green); // fill color
    rectangle2.setFillColor(sf::Color::Green); // fill color
    rectangle.setPosition(200, 600); // position in the middle of the window
    rectangle2.setPosition(1400, 600); // position in the middle of the window

    // permet animation player 1
    int currentFrame = 0;
    sf::Clock animationClock;
    bool isRunning = false;
    bool isRunningL = false;
    firstPlayer.isRunning = isRunning;
    firstPlayer.isRunningL = isRunningL;
    bool isJumping = false;
    firstPlayer.isJumping = isJumping;
    bool isCrouch = false;
    firstPlayer.isCrouch = isCrouch;
    bool cannotMove1 = false;
    firstPlayer.cannotMove = cannotMove1;
    bool isAttack1 = false;
    bool isAttack2 = false;
    bool isAttack3 = false;
    firstPlayer.isAttack1 = isAttack1;
    firstPlayer.isAttack2 = isAttack2;
    firstPlayer.isAttack3 = isAttack3;
    bool isDie = false;
    firstPlayer.isDie = isDie;

    // permet animation player 2
    int currentFrame2 = 0;
    sf::Clock animationClock2;
    bool isRunning2 = false;
    bool isRunningL2 = false;
    secondPlayer.isRunning = isRunning2;
    secondPlayer.isRunningL = isRunningL2;
    bool isJumping2 = false;
    secondPlayer.isJumping = isJumping2;
    bool isCrouch2 = false;
    secondPlayer.isCrouch = isCrouch2;
    bool cannotMove2 = false;
    secondPlayer.cannotMove = cannotMove2;
    bool isAttack12 = false;
    bool isAttack22 = false;
    secondPlayer.isAttack1 = isAttack12;
    secondPlayer.isAttack2 = isAttack22;
    bool isDie2 = false;
    secondPlayer.isDie = isDie2;

    float gravity = 0.5f; // gravity force (decreased for longer jumps)
    float velocity1; // initial vertical velocity
    firstPlayer.velocity = velocity1;
    float velocity2; // initial vertical velocity
    secondPlayer.velocity = velocity2;
    int jumps1 = 0; // number of jumps since the last ground contact
    firstPlayer.jumps = jumps1;
    int jumps2 = 0; // number of jumps since the last ground contact
    secondPlayer.jumps = jumps2;
    bool wasZPressed = false;
    firstPlayer.wasZPressed = wasZPressed;
    bool wasYPressed = false;
    secondPlayer.wasZPressed = wasYPressed;
    bool lastDirectionLeft = false; // was the space key pressed during the last iteration?
    firstPlayer.lastDirectionLeft = lastDirectionLeft;
    bool lastDirectionLeft2 = false;
    secondPlayer.lastDirectionLeft = lastDirectionLeft2;

    // Player 1 dash
    bool isDashing1 = false;
    firstPlayer.isDashing = isDashing1;
    float dashDirection1 = 0.0f;
    firstPlayer.dashDirection = dashDirection1;
    float dashDistance1 = 0.0f;
    firstPlayer.dashDistance = dashDistance1;
    sf::Clock dashClock1;

    // Player 2 dash
    bool isDashing2 = false;
    secondPlayer.isDashing = isDashing2;
    float dashDirection2 = 0.0f;
    secondPlayer.dashDirection = dashDirection2;
    float dashDistance2 = 0.0f;
    secondPlayer.dashDistance = dashDistance2;
    sf::Clock dashClock2;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // *** PLAYER 1 ATTACKS ***

        // attack1 player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            firstPlayer.isAttack1 = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % ATTACKLCharecterSheet.size();
                    Player.setTexture(ATTACKLCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % ATTACKCharecterSheet.size();
                    Player.setTexture(ATTACKCharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        } else {
            firstPlayer.isAttack1 = false;
        }

        // attack2 player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            firstPlayer.isAttack2 = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % ATTACK2LCharecterSheet.size();
                    Player.setTexture(ATTACK2LCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % ATTACK2CharecterSheet.size();
                    Player.setTexture(ATTACK2CharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        } else {
            firstPlayer.isAttack2 = false;
        }

        
        // attack3 player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            firstPlayer.isAttack3 = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % ATTACK3LCharecterSheet.size();
                    Player.setTexture(ATTACK3LCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % ATTACK3CharecterSheet.size();
                    Player.setTexture(ATTACK3CharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        } else {
            firstPlayer.isAttack3 = false;
        }

        // *** PLAYER 2 ATTACKS ***

        // attack1 player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)) {
            secondPlayer.isAttack1 = true;
            // update the sprite every 0.1 seconds
            if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft2) {
                    currentFrame2 = (currentFrame2 + 1) % ATTACKLCharecterSheet2.size();
                    Player2.setTexture(ATTACKLCharecterSheet2[currentFrame2]);
                } else {
                    currentFrame2 = (currentFrame2 + 1) % ATTACKCharecterSheet2.size();
                    Player2.setTexture(ATTACKCharecterSheet2[currentFrame2]);
                }
                animationClock2.restart();
            }
        } else {
            secondPlayer.isAttack1 = false;
        }

        // attack2 player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            secondPlayer.isAttack2 = true;
            // update the sprite every 0.1 seconds
            if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft2) {
                    currentFrame2 = (currentFrame2 + 1) % ATTACK2LCharecterSheet2.size();
                    Player2.setTexture(ATTACK2LCharecterSheet2[currentFrame2]);
                } else {
                    currentFrame2 = (currentFrame2 + 1) % ATTACK2CharecterSheet2.size();
                    Player2.setTexture(ATTACK2CharecterSheet2[currentFrame2]);
                }
                animationClock2.restart();
            }
        } else {
            secondPlayer.isAttack2 = false;
        }

        // attack3 player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            secondPlayer.isAttack3 = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % ATTACK3LCharecterSheet.size();
                    Player2.setTexture(ATTACK3LCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % ATTACK3CharecterSheet.size();
                    Player2.setTexture(ATTACK3CharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        } else {
            secondPlayer.isAttack3 = false;
        }
        

        // die player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            firstPlayer.isDie = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                currentFrame = (currentFrame + 1) % DIECharecterSheet.size();
                Player.setTexture(DIECharecterSheet[currentFrame]);
                animationClock.restart();
            }
        } else {
            firstPlayer.isDie = false;
        }

        // die player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            secondPlayer.isDie = true;
            // update the sprite every 0.1 seconds
            if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                currentFrame2 = (currentFrame2 + 1) % DIECharecterSheet2.size();
                Player2.setTexture(DIECharecterSheet2[currentFrame2]);
                animationClock2.restart();
            }
        } else {
            secondPlayer.isDie = false;
        }

        // crouch player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            firstPlayer.isCrouch = true;
            firstPlayer.cannotMove = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % CRHLCharecterSheet.size();
                    Player.setTexture(CRHLCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % CRHCharecterSheet.size();
                    Player.setTexture(CRHCharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        } else {
            firstPlayer.isCrouch = false;
            firstPlayer.cannotMove = false;
        }

        // crouch player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            secondPlayer.isCrouch = true;
            secondPlayer.cannotMove = true;
            // update the sprite every 0.1 seconds
            if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft2) {
                    currentFrame2 = (currentFrame2 + 1) % CRHLCharecterSheet2.size();
                    Player2.setTexture(CRHLCharecterSheet2[currentFrame2]);
                } else {
                    currentFrame2 = (currentFrame2 + 1) % CRHCharecterSheet2.size();
                    Player2.setTexture(CRHCharecterSheet2[currentFrame2]);
                }
                animationClock2.restart();
            }
        } else {
            secondPlayer.isCrouch = false;
            secondPlayer.cannotMove = false;
        }

        // jump and condition player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            firstPlayer.isJumping = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (firstPlayer.lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % JMPLCharecterSheet.size();
                    Player.setTexture(JMPLCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % JMPCharecterSheet.size();
                    Player.setTexture(JMPCharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        } else {
            firstPlayer.isJumping = false;
        }

        if (!firstPlayer.isJumping) {
            if (firstPlayer.isCrouch){
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                firstPlayer.isRunning = true;
                firstPlayer.lastDirectionLeft = false;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runningCharacterSheet.size();
                    Player.setTexture(runningCharacterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else {
                firstPlayer.isRunning = false;
            }
            if (firstPlayer.isCrouch){
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                firstPlayer.isRunningL = true;
                firstPlayer.lastDirectionLeft = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runLCharecterSheet.size();
                    Player.setTexture(runLCharecterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else {
                firstPlayer.isRunningL = false;
            }
        }

        if (!firstPlayer.isJumping && !firstPlayer.isRunning && !firstPlayer.isRunningL && !firstPlayer.isCrouch) {
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (firstPlayer.lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % IdleLCharacterSheet.size();
                    Player.setTexture(IdleLCharacterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % IdleCharacterSheet.size();
                    Player.setTexture(IdleCharacterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        }

        // jump and condition player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            secondPlayer.isJumping = true;
            // update the sprite every 0.1 seconds
            if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                if (secondPlayer.lastDirectionLeft) {
                    currentFrame2 = (currentFrame2 + 1) % JMPLCharecterSheet2.size();
                    Player2.setTexture(JMPLCharecterSheet2[currentFrame2]);
                } else {
                    currentFrame2 = (currentFrame2 + 1) % JMPCharecterSheet2.size();
                    Player2.setTexture(JMPCharecterSheet2[currentFrame2]);
                }
                animationClock2.restart();
            }
        } else {
            secondPlayer.isJumping = false;
        }

        if (!secondPlayer.isJumping) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                secondPlayer.isRunning = true;
                secondPlayer.lastDirectionLeft = false;
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame2 = (currentFrame2 + 1) % RunCharacterSheet2.size();
                    Player2.setTexture(RunCharacterSheet2[currentFrame2]);
                    animationClock2.restart();
                }
            } else {
                secondPlayer.isRunning = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                secondPlayer.isRunningL = true;
                secondPlayer.lastDirectionLeft = true;
                // update the sprite every 0.1 seconds
                if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame2 = (currentFrame2 + 1) % RunLCharacterSheet2.size();
                    Player2.setTexture(RunLCharacterSheet2[currentFrame2]);
                    animationClock2.restart();
                }
            } else {
                secondPlayer.isRunningL = false;
            }
        }

        if (!secondPlayer.isJumping && !secondPlayer.isRunning && !secondPlayer.isRunningL && !secondPlayer.isCrouch) {
            // update the sprite every 0.1 seconds
            if (animationClock2.getElapsedTime().asSeconds() > 0.1f) {
                if (secondPlayer.lastDirectionLeft) {
                    currentFrame2 = (currentFrame2 + 1) % IdleLCharacterSheet2.size();
                    Player2.setTexture(IdleLCharacterSheet2[currentFrame2]);
                } else {
                    currentFrame2 = (currentFrame2 + 1) % IdleCharacterSheet2.size();
                    Player2.setTexture(IdleCharacterSheet2[currentFrame2]);
                }
                animationClock2.restart();
            }
        }
        // apply gravity
        float dy1 = firstPlayer.velocity; // save the current velocity for Player1
        float dy2 = secondPlayer.velocity; // save the current velocity for Player2
        firstPlayer.velocity += gravity;
        secondPlayer.velocity += gravity;
        Player.move(0, firstPlayer.velocity);
        Player2.move(0, secondPlayer.velocity);

        // collision player 1
        if (Player.getGlobalBounds().intersects(rectangle.getGlobalBounds())){
            firstPlayer.velocity = 0.0f;
            firstPlayer.jumps = 0;
            Player.setPosition(Player.getPosition().x, rectangle.getPosition().y - Player.getGlobalBounds().height);   
        }

        if (Player.getGlobalBounds().intersects(rectangle2.getGlobalBounds())){
            firstPlayer.velocity = 0.0f;
            firstPlayer.jumps = 0;
            Player.setPosition(Player.getPosition().x, rectangle2.getPosition().y - Player.getGlobalBounds().height);   
        }

        if (Player.getPosition().y + Player.getGlobalBounds().height > window.getSize().y)
        {
            Player.setPosition(Player.getPosition().x, window.getSize().y - Player.getGlobalBounds().height);
            firstPlayer.velocity = 0.0f;
            firstPlayer.jumps = 0;
        }

        // collision player 2
        if (Player2.getGlobalBounds().intersects(rectangle.getGlobalBounds())){
            secondPlayer.velocity = 0.0f;
            secondPlayer.jumps = 0;
            Player2.setPosition(Player2.getPosition().x, rectangle.getPosition().y - Player2.getGlobalBounds().height);   
        }

        if (Player2.getGlobalBounds().intersects(rectangle2.getGlobalBounds())){
            secondPlayer.velocity = 0.0f;
            secondPlayer.jumps = 0;
            Player2.setPosition(Player2.getPosition().x, rectangle2.getPosition().y - Player2.getGlobalBounds().height);   
        }

        if (Player2.getPosition().y + Player2.getGlobalBounds().height > window.getSize().y)
        {
            Player2.setPosition(Player2.getPosition().x, window.getSize().y - Player2.getGlobalBounds().height);
            secondPlayer.velocity = 0.0f;
            secondPlayer.jumps = 0;
        }

        // jump player 1
        firstPlayer.isZPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
        if (firstPlayer.isZPressed && !firstPlayer.wasZPressed && firstPlayer.jumps < 2)
        {
            firstPlayer.velocity = firstPlayer.jumps == 0 ? -16.0f : -16.0f; // higher jump for the second jump
            firstPlayer.jumps++;
        }
        firstPlayer.wasZPressed = firstPlayer.isZPressed;

        // jump player 2
        secondPlayer.isZPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
        if (secondPlayer.isZPressed && !secondPlayer.wasZPressed && secondPlayer.jumps < 2)
        {
            secondPlayer.velocity = secondPlayer.jumps == 0 ? -16.0f : -16.0f; // higher jump for the second jump
            secondPlayer.jumps++;
        }
        secondPlayer.wasZPressed = secondPlayer.isZPressed;

        // move the player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && Player.getGlobalBounds().left > 0 && !(firstPlayer.cannotMove))
            Player.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x && !(firstPlayer.cannotMove))
            Player.move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Player.getGlobalBounds().top + Player.getGlobalBounds().height < window.getSize().y)
            Player.move(0, 12);

        // move the player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && Player2.getGlobalBounds().left > 0 && !(secondPlayer.cannotMove))
            Player2.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x && !(secondPlayer.cannotMove))
            Player2.move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && Player2.getGlobalBounds().top + Player2.getGlobalBounds().height < window.getSize().y)
            Player2.move(0, 8);

        // dash the player 1
        sf::Time timeSinceLastDash1 = dashClock1.getElapsedTime();
        if (!firstPlayer.isDashing && timeSinceLastDash1.asSeconds() >= 5.0f) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Player.getGlobalBounds().left > 0) {
                firstPlayer.isDashing = true;
                firstPlayer.dashDirection = -20.0f;
                dashClock1.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x) {
                firstPlayer.isDashing = true;
                firstPlayer.dashDirection = 20.0f;
                dashClock1.restart();
            }
        }

        if (firstPlayer.isDashing) {
            if (firstPlayer.dashDistance < 500.0f) {
                if ((firstPlayer.dashDirection < 0 && Player.getGlobalBounds().left > 0) || 
                    (firstPlayer.dashDirection > 0 && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x)) {
                    Player.move(firstPlayer.dashDirection, 0);
                    firstPlayer.dashDistance += std::abs(firstPlayer.dashDirection);
                } else {
                    firstPlayer.isDashing = false;
                    firstPlayer.dashDistance = 0.0f;
                }
            } else {
                firstPlayer.isDashing = false;
                firstPlayer.dashDistance = 0.0f;
            }
        }

        // dash the player 2
        sf::Time timeSinceLastDash2 = dashClock2.getElapsedTime();
        if (!secondPlayer.isDashing && timeSinceLastDash2.asSeconds() >= 5.0f) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && Player2.getGlobalBounds().left > 0) {
                secondPlayer.isDashing = true;
                secondPlayer.dashDirection = 20.0f;
                dashClock2.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x) {
                secondPlayer.isDashing = true;
                secondPlayer.dashDirection = -20.0f;
                dashClock2.restart();
            }
        }

        if (secondPlayer.isDashing) {
            if (secondPlayer.dashDistance < 500.0f) {
                if ((secondPlayer.dashDirection < 0 && Player2.getGlobalBounds().left > 0) || 
                    (secondPlayer.dashDirection > 0 && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x)) {
                    Player2.move(secondPlayer.dashDirection, 0);
                    secondPlayer.dashDistance += std::abs(secondPlayer.dashDirection);
                } else {
                    secondPlayer.isDashing = false;
                    secondPlayer.dashDistance = 0.0f;
                }
            } else {
                secondPlayer.isDashing = false;
                secondPlayer.dashDistance = 0.0f;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(s);
        window.draw(Player);
        window.draw(Player2);
        window.draw(rectangle);
        window.draw(rectangle2);
        window.display();
    }

    return 0;
}
