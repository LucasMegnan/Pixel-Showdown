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
    std::vector<sf::Texture> ATTACK2CharecterSheet = loadCharacterSheet("Imgs/Characters/attack2");
    std::vector<sf::Texture> ATTACK3CharecterSheet = loadCharacterSheet("Imgs/Characters/attack3");
    std::vector<sf::Texture> DIECharecterSheet = loadCharacterSheet("Imgs/Characters/die");
    
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
    float velocity = 0.0f; // initial vertical velocity
    int jumps = 0; // number of jumps since the last ground contact
    bool wasZPressed = false;
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            isAttack1 = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                currentFrame = (currentFrame + 1) % ATTACKCharecterSheet.size();
                Player.setTexture(ATTACKCharecterSheet[currentFrame]);
                animationClock.restart();
            }
        } else {
            isAttack1 = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            isAttack2 = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                currentFrame = (currentFrame + 1) % ATTACK2CharecterSheet.size();
                Player.setTexture(ATTACK2CharecterSheet[currentFrame]);
                animationClock.restart();
            }
        } else {
            isAttack2 = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            isAttack3 = true;
            // update the sprite every 0.1 seconds
            if (animationClock.getElapsedTime().asSeconds() > 0.1f) {
                currentFrame = (currentFrame + 1) % ATTACK3CharecterSheet.size();
                Player.setTexture(ATTACK3CharecterSheet[currentFrame]);
                animationClock.restart();
            }
        } else {
            isAttack3 = false;
        }

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
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

        // apply gravity
        float dy = velocity; // save the current velocity
        velocity += gravity;
        Player.move(0, velocity);

        if (Player.getGlobalBounds().intersects(rectangle.getGlobalBounds())){
            velocity = 0.0f;
            jumps = 0;
            Player.setPosition(Player.getPosition().x, rectangle.getPosition().y - Player.getGlobalBounds().height);   
        }

        if (Player.getGlobalBounds().intersects(rectangle2.getGlobalBounds())){
            velocity = 0.0f;
            jumps = 0;
            Player.setPosition(Player.getPosition().x, rectangle2.getPosition().y - Player.getGlobalBounds().height);   
        }

        // collision with the bottom of the screen
        if (Player.getPosition().y + Player.getGlobalBounds().height > window.getSize().y)
        {
            Player.setPosition(Player.getPosition().x, window.getSize().y - Player.getGlobalBounds().height);
            velocity = 0.0f;
            jumps =  0;
        }

        // jump
        bool isZPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (isZPressed && !wasZPressed && jumps < 2)
        {
            velocity = jumps == 0 ? -8.0f : -8.0f; // higher jump for the second jump
            jumps++;
        }
        wasZPressed = isZPressed;

        // move the player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && Player.getGlobalBounds().left > 0)
            Player.move(-3, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Player.getGlobalBounds().left + Player.getGlobalBounds().width < window.getSize().x)
            Player.move(3, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Player.getGlobalBounds().top + Player.getGlobalBounds().height < window.getSize().y)
            Player.move(0, 15);

        // dash the player
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

        window.clear(sf::Color::Black);
        window.draw(s);
        window.draw(Player);
        window.draw(rectangle);
        window.draw(rectangle2);
        window.display();
    }

    return 0;
}
