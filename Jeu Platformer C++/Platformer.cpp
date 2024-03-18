#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>

// load character sheet
std::vector<sf::Texture> loadCharacterSheet(const std::string& directoryPath) {
    std::vector<sf::Texture> textures;
    for (const auto & entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.path().extension() == ".png") {
            sf::Texture texture;
            if (texture.loadFromFile(entry.path().string())) {
                textures.push_back(std::move(texture));
            }
        }
    }
    return textures;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Le jeu de la mort qui tue", sf::Style::Fullscreen);
    sf::Texture t;
    t.loadFromFile("imgs/image.png");
    sf::Sprite s(t);
    window.setVerticalSyncEnabled(true);


    // Charger la feuille de personnage
    std::vector<sf::Texture> characterSheet = loadCharacterSheet("Imgs/Characters/Idle");
    std::vector<sf::Texture> characterSheetL = loadCharacterSheet("Imgs/Characters/IdleL");
    std::vector<sf::Texture> runningCharacterSheet = loadCharacterSheet("Imgs/Characters/Run");
    std::vector<sf::Texture> runLCharecterSheet = loadCharacterSheet("Imgs/Characters/RunL");
    std::vector<sf::Texture> JMPCharecterSheet = loadCharacterSheet("Imgs/Characters/Jmp");
    std::vector<sf::Texture> JMPLCharecterSheet = loadCharacterSheet("Imgs/Characters/JmpL");
    std::vector<sf::Texture> CRHCharecterSheet = loadCharacterSheet("Imgs/Characters/Crh");
    std::vector<sf::Texture> CRHLCharecterSheet = loadCharacterSheet("Imgs/Characters/CrhL");
    std::vector<sf::Texture> ATTACKCharecterSheet = loadCharacterSheet("Imgs/Characters/attack1");
    std::vector<sf::Texture> ATTACKLCharecterSheet = loadCharacterSheet("Imgs/Characters/attack1L");
    std::vector<sf::Texture> ATTACK2CharecterSheet = loadCharacterSheet("Imgs/Characters/attack2");
    std::vector<sf::Texture> ATTACK2LCharecterSheet = loadCharacterSheet("Imgs/Characters/attack2L");
    std::vector<sf::Texture> ATTACK3CharecterSheet = loadCharacterSheet("Imgs/Characters/attack3");
    std::vector<sf::Texture> ATTACK3LCharecterSheet = loadCharacterSheet("Imgs/Characters/attack3L");
    std::vector<sf::Texture> DIECharecterSheet = loadCharacterSheet("Imgs/Characters/die");

    //Créer un sprite pour le joueur 2
    sf::Sprite Player2;
    Player2.setTexture(characterSheet[0]);
    Player2.setScale(sf::Vector2f(3.0f, 3.0)); // Ajuster la taille du sprite si nécessaire
    Player2.setPosition(200, 200);
    
    // Créer un sprite pour le joueur
    sf::Sprite Player;
    Player.setTexture(characterSheet[0]);
    Player.setScale(sf::Vector2f(3.0f, 3.0)); // Ajuster la taille du sprite si nécessaire
    Player.setPosition(375, 275);


    sf::RectangleShape rectangle(sf::Vector2f(300, 20)); // circle with radius 50
    sf::RectangleShape rectangle2(sf::Vector2f(300, 20)); // circle with radius 50
    rectangle.setFillColor(sf::Color::Red); // fill color
    rectangle2.setFillColor(sf::Color::Red); // fill color
    rectangle.setPosition(200, 600); // position in the middle of the window
    rectangle2.setPosition(1400, 600); // position in the middle of the window


    // permet animation
    int currentFrame = 0;
    sf::Clock animationClock;
    bool isRunning = false;
    bool isRunningL = false;
    bool isJumping = false;
    bool isCrouch = false;
    bool isAttack1 = false;
    bool isAttack2 = false;
    bool isAttack3 = false;
    bool isDie = false;

    float gravity = 0.1f; // gravity force (decreased for longer jumps)
    float velocity1 = 0.0f; // initial vertical velocity
    float velocity2 = 0.0f; // initial vertical velocity
    int jumps1 = 0; // number of jumps since the last ground contact
    int jumps2 = 0; // number of jumps since the last ground contact
    bool wasZPressed = false;
    bool wasYPressed = false;
    bool lastDirectionLeft = false; // was the space key pressed during the last iteration?

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

        // attack1 player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            isAttack1 = true;
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
            isAttack1 = false;
        }

        // attack1 player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)) {
            isAttack1 = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % ATTACKLCharecterSheet.size();
                    Player2.setTexture(ATTACKLCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % ATTACKCharecterSheet.size();
                    Player2.setTexture(ATTACKCharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        } else {
            isAttack1 = false;
        }

        // attack2 player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            isAttack2 = true;
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
        }

        // attack2 player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            isAttack2 = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % ATTACK2LCharecterSheet.size();
                    Player2.setTexture(ATTACK2LCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % ATTACK2CharecterSheet.size();
                    Player2.setTexture(ATTACK2CharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        }

        // attack3 player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            isAttack3 = true;
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
        }

        // attack3 player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            isAttack3 = true;
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
        }

        // die player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            isDie = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                currentFrame = (currentFrame + 1) % DIECharecterSheet.size();
                Player.setTexture(DIECharecterSheet[currentFrame]);
                animationClock.restart();
            }
        } else {
            isDie = false;
        }

        // die player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
            isDie = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                currentFrame = (currentFrame + 1) % DIECharecterSheet.size();
                Player2.setTexture(DIECharecterSheet[currentFrame]);
                animationClock.restart();
            }
        } else {
            isDie = false;
        }

        // crouch, run player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                isRunning = true;
                lastDirectionLeft = false;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runningCharacterSheet.size();
                    Player.setTexture(runningCharacterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                isRunningL = true;
                lastDirectionLeft = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runLCharecterSheet.size();
                    Player.setTexture(runLCharecterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else {
                isCrouch = true;
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
            }
        } else {
            isCrouch = false;
        }

        // crouch, run player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                isRunning = true;
                lastDirectionLeft = false;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runningCharacterSheet.size();
                    Player2.setTexture(runningCharacterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                isRunningL = true;
                lastDirectionLeft = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runLCharecterSheet.size();
                    Player2.setTexture(runLCharecterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else {
                isCrouch = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    if (lastDirectionLeft) {
                        currentFrame = (currentFrame + 1) % CRHLCharecterSheet.size();
                        Player2.setTexture(CRHLCharecterSheet[currentFrame]);
                    } else {
                        currentFrame = (currentFrame + 1) % CRHCharecterSheet.size();
                        Player2.setTexture(CRHCharecterSheet[currentFrame]);
                    }
                    animationClock.restart();
                }
            }
        } else {
            isCrouch = false;
        }

        // jump and condition player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            isJumping = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % JMPLCharecterSheet.size();
                    Player.setTexture(JMPLCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % JMPCharecterSheet.size();
                    Player.setTexture(JMPCharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        } else {
            isJumping = false;
        }

        if (!isJumping) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                isRunning = true;
                lastDirectionLeft = false;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runningCharacterSheet.size();
                    Player.setTexture(runningCharacterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else {
                isRunning = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                isRunningL = true;
                lastDirectionLeft = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runLCharecterSheet.size();
                    Player.setTexture(runLCharecterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else {
                isRunningL = false;
            }
        }

        if (!isJumping && !isRunning && !isRunningL && !isCrouch) {
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % characterSheetL.size();
                    Player.setTexture(characterSheetL[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % characterSheet.size();
                    Player.setTexture(characterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        }

        // jump and condition player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            isJumping = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % JMPLCharecterSheet.size();
                    Player2.setTexture(JMPLCharecterSheet[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % JMPCharecterSheet.size();
                    Player2.setTexture(JMPCharecterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        } else {
            isJumping = false;
        }

        if (!isJumping) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                isRunning = true;
                lastDirectionLeft = false;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runningCharacterSheet.size();
                    Player2.setTexture(runningCharacterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else {
                isRunning = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                isRunningL = true;
                lastDirectionLeft = true;
                // update the sprite every 0.1 seconds
                if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                    currentFrame = (currentFrame + 1) % runLCharecterSheet.size();
                    Player2.setTexture(runLCharecterSheet[currentFrame]);
                    animationClock.restart();
                }
            } else {
                isRunningL = false;
            }
        }

        if (!isJumping && !isRunning && !isRunningL && !isCrouch) {
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                if (lastDirectionLeft) {
                    currentFrame = (currentFrame + 1) % characterSheetL.size();
                    Player2.setTexture(characterSheetL[currentFrame]);
                } else {
                    currentFrame = (currentFrame + 1) % characterSheet.size();
                    Player2.setTexture(characterSheet[currentFrame]);
                }
                animationClock.restart();
            }
        }

        // apply gravity
        float dy1 = velocity1; // save the current velocity for Player1
        float dy2 = velocity2; // save the current velocity for Player2
        velocity1 += gravity;
        velocity2 += gravity;
        Player.move(0, velocity1);
        Player2.move(0, velocity2);

        // collision player 1
        if (Player.getGlobalBounds().intersects(rectangle.getGlobalBounds())){
            velocity1 = 0.0f;
            jumps1 = 0;
            Player.setPosition(Player.getPosition().x, rectangle.getPosition().y - Player.getGlobalBounds().height);   
        }

        if (Player.getGlobalBounds().intersects(rectangle2.getGlobalBounds())){
            velocity1 = 0.0f;
            jumps1 = 0;
            Player.setPosition(Player.getPosition().x, rectangle2.getPosition().y - Player.getGlobalBounds().height);   
        }

        if (Player.getPosition().y + Player.getGlobalBounds().height > window.getSize().y)
        {
            Player.setPosition(Player.getPosition().x, window.getSize().y - Player.getGlobalBounds().height);
            velocity1 = 0.0f;
            jumps1 =  0;
        }

        // collision player 2
        if (Player2.getGlobalBounds().intersects(rectangle.getGlobalBounds())){
            velocity2 = 0.0f;
            jumps2 = 0;
            Player2.setPosition(Player2.getPosition().x, rectangle.getPosition().y - Player2.getGlobalBounds().height);   
        }

        if (Player2.getGlobalBounds().intersects(rectangle2.getGlobalBounds())){
            velocity2 = 0.0f;
            jumps2 = 0;
            Player2.setPosition(Player2.getPosition().x, rectangle2.getPosition().y - Player2.getGlobalBounds().height);   
        }

        if (Player2.getPosition().y + Player2.getGlobalBounds().height > window.getSize().y)
        {
            Player2.setPosition(Player2.getPosition().x, window.getSize().y - Player2.getGlobalBounds().height);
            velocity2 = 0.0f;
            jumps2 =  0;
        }

        // jump player 1
        bool isZPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
        if (isZPressed && !wasZPressed && jumps1 < 2)
        {
            velocity1 = jumps1 == 0 ? -8.0f : -8.0f; // higher jump for the second jump
            jumps1++;
        }
        wasZPressed = isZPressed;

        // jump player 2
        bool isYPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
        if (isYPressed && !wasYPressed && jumps2 < 2)
        {
            velocity2 = jumps2 == 0 ? -8.0f : -8.0f; // higher jump for the second jump
            jumps2++;
        }
        wasYPressed = isYPressed;

        // move the player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && Player.getGlobalBounds().left > 0)
            Player.move(-3, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x)
            Player.move(3, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Player.getGlobalBounds().top + Player.getGlobalBounds().height < window.getSize().y)
            Player.move(0, 6);

        // move the player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && Player2.getGlobalBounds().left > 0)
            Player2.move(-3, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x)
            Player2.move(3, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && Player2.getGlobalBounds().top + Player2.getGlobalBounds().height < window.getSize().y)
            Player2.move(0, 6);

        // dash the player 1
        sf::Time timeSinceLastDash = dashClock.getElapsedTime();
        if (!isDashing && timeSinceLastDash.asSeconds() >= 5.0f) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Player.getGlobalBounds().left > 0) {
                isDashing = true;
                dashDirection = -20.0f;
                dashClock.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x) {
                isDashing = true;
                dashDirection = 20.0f;
                dashClock.restart();
            }
        }

        if (isDashing) {
            if (dashDistance < 500.0f) {
                if ((dashDirection < 0 && Player.getGlobalBounds().left > 0) || 
                    (dashDirection > 0 && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x)) {
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

        // dash the player 2
        sf::Time timeSinceLastDash2 = dashClock.getElapsedTime();
        if (!isDashing && timeSinceLastDash2.asSeconds() >= 5.0f) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) && Player2.getGlobalBounds().left > 0) {
                isDashing = true;
                dashDirection = -20.0f;
                dashClock.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x) {
                isDashing = true;
                dashDirection = 20.0f;
                dashClock.restart();
            }
        }

        if (isDashing) {
            if (dashDistance < 500.0f) {
                if ((dashDirection < 0 && Player2.getGlobalBounds().left > 0) || 
                    (dashDirection > 0 && Player2.getGlobalBounds().left + Player2.getGlobalBounds().width < window.getSize().x)) {
                    Player2.move(dashDirection, 0);
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
        window.draw(Player2);
        window.draw(rectangle);
        window.draw(rectangle2);
        window.display();
    }

    return 0;
}
