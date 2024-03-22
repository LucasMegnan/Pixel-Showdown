#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <SFML/Audio.hpp>
#include "Platformer.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pixel Showdown", sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    sf::Music music;
    if (!music.openFromFile("Music/menu.wav")) {
        // handle error
    }
    music.setLoop(true); // to loop the music
    music.play();

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Music/buttoneffect.wav")) {
        // handle error
    }
    sf::Sound clickSound;
    clickSound.setBuffer(buffer);

    sf::Font font;
    if (!font.loadFromFile("againts.otf")) {
        // handle error
    }

    sf::Text playButton("Play", font);
    playButton.setPosition(100, 300);
    playButton.setFillColor(sf::Color::Red);
    playButton.setScale(2, 2);
    
    sf::Text howToPlayButton("How to play", font);
    howToPlayButton.setPosition(100, 400);
    howToPlayButton.setFillColor(sf::Color::White);
    howToPlayButton.setScale(2, 2);

    sf::Text settingsButton("Settings", font);
    settingsButton.setPosition(100, 500);
    settingsButton.setFillColor(sf::Color::White);
    settingsButton.setScale(2, 2);

    sf::Text exitButton("Exit", font);
    exitButton.setPosition(100, 600);
    exitButton.setFillColor(sf::Color::White);
    exitButton.setScale(2, 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    music.stop();
                    launchGame(window);
                    return 0;
                }
                if (howToPlayButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    clickSound.play();
                }
                if (settingsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    clickSound.play();
                }
                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                }
            //}
        }

        window.clear(sf::Color::Black);
        window.draw(playButton);
        window.draw(howToPlayButton);
        window.draw(settingsButton);
        window.draw(exitButton);
        window.display();
    }

    return 0;
}