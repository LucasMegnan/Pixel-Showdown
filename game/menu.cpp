#include <SFML/Graphics.hpp>
#include <filesystem>
#include <vector>
#include <SFML/Audio.hpp>
#include "Platformer.h"


void updateChoicePosition(int& choicePos, int increment, int minValue, int maxValue) {
    // Move the choice position by the specified increment/decrement
    choicePos += increment;

    if (choicePos < minValue) {
        choicePos = maxValue;
    } 
    else if (choicePos > maxValue) {
        choicePos = minValue;
    }
}

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

    sf::Text Title("Pixel Showdown", font);
    Title.setPosition(700, 150);
    Title.setFillColor(sf::Color::Cyan);
    Title.setScale(3, 3);

    int playButtonPos = 400;
    sf::Text playButton("Play", font);
    playButton.setPosition(100, playButtonPos);
    playButton.setFillColor(sf::Color::White);
    playButton.setScale(2, 2);
    
    int howToPlayButtonPos = 500;
    sf::Text howToPlayButton("How to play", font);
    howToPlayButton.setPosition(100, howToPlayButtonPos);
    howToPlayButton.setFillColor(sf::Color::White);
    howToPlayButton.setScale(2, 2);

    int settingsButtonPos = 600;
    sf::Text settingsButton("Settings", font);
    settingsButton.setPosition(100, settingsButtonPos);
    settingsButton.setFillColor(sf::Color::White);
    settingsButton.setScale(2, 2);

    int exitButtonPos = 700;
    sf::Text exitButton("Exit", font);
    exitButton.setPosition(100, exitButtonPos);
    exitButton.setFillColor(sf::Color::White);
    exitButton.setScale(2, 2);

    int choicePos = playButtonPos;

    bool isZPressed = false;
    bool isSPressed = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            // *** Color Update depending on your choice ***
            if (choicePos == playButtonPos) {
                playButton.setFillColor(sf::Color::Red);
                howToPlayButton.setFillColor(sf::Color::White);
                settingsButton.setFillColor(sf::Color::White);
                exitButton.setFillColor(sf::Color::White);
            }
            else if (choicePos == howToPlayButtonPos) {
                playButton.setFillColor(sf::Color::White);
                howToPlayButton.setFillColor(sf::Color::Red);
                settingsButton.setFillColor(sf::Color::White);
                exitButton.setFillColor(sf::Color::White);
            }
            else if (choicePos == settingsButtonPos) {
                playButton.setFillColor(sf::Color::White);
                howToPlayButton.setFillColor(sf::Color::White);
                settingsButton.setFillColor(sf::Color::Red);
                exitButton.setFillColor(sf::Color::White);
            }
            else if (choicePos == exitButtonPos) { 
                playButton.setFillColor(sf::Color::White);
                howToPlayButton.setFillColor(sf::Color::White);
                settingsButton.setFillColor(sf::Color::White);
                exitButton.setFillColor(sf::Color::Red);
            }

            // Update the choice position
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isSPressed) {
                updateChoicePosition(choicePos, 50, playButtonPos, exitButtonPos);
            } 
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !isZPressed) {
                updateChoicePosition(choicePos, -50, playButtonPos, exitButtonPos);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && choicePos == playButtonPos) { // checks if you're on the Play button
                music.stop();
                launchGame(window);
                return 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && choicePos == howToPlayButtonPos) { // checks if you're on the How to Play button
                clickSound.play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && choicePos == settingsButtonPos) { // checks if you're on the Settings button
                clickSound.play();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && choicePos == exitButtonPos) { // checks if you're on the Exit button
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(Title);
        window.draw(playButton);
        window.draw(howToPlayButton);
        window.draw(settingsButton);
        window.draw(exitButton);
        window.display();
    }

    return 0;
}
