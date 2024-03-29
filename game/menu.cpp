#include "Platformer.h"

bool wasZPressed = false;
bool wasSPressed = false;

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

void howToPlay(sf::RenderWindow& window, sf::Font font){
    sf::Text howToPlayText("How to play?", font);
    howToPlayText.setPosition(700, 75);
    howToPlayText.setFillColor(sf::Color::Yellow);
    howToPlayText.setScale(4, 4);

    sf::Text instructions("Joystick to move\nClick Joystick to crouch\nA  to jump\nB  to dash\nX-Y  to attack", font);
    instructions.setPosition(300, 300);
    instructions.setFillColor(sf::Color::Magenta);
    instructions.setScale(2, 2);

    sf::Text Return("Press Select to return", font);
    Return.setPosition(775, 900);
    Return.setFillColor(sf::Color::Yellow);
    Return.setScale(1.5, 1.5);

    sf::Joystick controller1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

            if (controller1.isButtonPressed(0, 6)){
                return;
            }
            
        window.clear(sf::Color::Black);
        window.draw(howToPlayText);
        window.draw(instructions);
        window.draw(Return);
        window.display();

    }
    return;
}

void charSelection (sf::RenderWindow& window, sf::Font font){
    sf::Music music;
    if (!music.openFromFile("Music/charSelection.wav")) {
        // handle error
    }
    music.setLoop(true); // to loop the music
    music.play();

    sf::Text ChooseCharacter ("Choose your Character", font);
    ChooseCharacter.setPosition(600, 150);
    ChooseCharacter.setFillColor(sf::Color::Magenta);
    ChooseCharacter.setScale(3, 3);

    sf::Texture t;
    t.loadFromFile("imgs/bg2.png");
    sf::Sprite s(t);

    sf::RectangleShape iconSquare(sf::Vector2f(125.0f, 125.0f));
    iconSquare.setFillColor(sf::Color::Magenta);
    iconSquare.setPosition(725, 700); 
    
    sf::RectangleShape iconSquare2(sf::Vector2f(125.0f, 125.0f));
    iconSquare2.setFillColor(sf::Color::Magenta);
    iconSquare2.setPosition(1040, 700); 

    sf::Sprite iconGuts;
    sf::Sprite iconShadr;
    sf::Sprite choose;

    sf::Texture charIconGuts;
    charIconGuts.loadFromFile("Imgs/Guts/icon.png");
    sf::Texture charIconShadr;
    charIconShadr.loadFromFile("Imgs/Shadr/icon.png");
    sf::Texture charChoose;
    charChoose.loadFromFile("Imgs/selectHand.png");

    int character;
    int GutsPos = 800;
    int ShadrPos = 1100;
    int choicePos = 950;

    int chosenChar1 = 0;
    int chosenChar2 = 0;

    sf::Joystick controller1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
            iconGuts.setPosition(700, 700);
            iconGuts.setTexture(charIconGuts);
            iconGuts.setScale(sf::Vector2f(3.0f, 3.0));
            iconShadr.setPosition(1050, 715);
            iconShadr.setTexture(charIconShadr);
            iconShadr.setScale(sf::Vector2f(3.0f, 3.0));
            choose.setPosition(choicePos, 800);
            choose.setTexture(charChoose);
            choose.setScale(sf::Vector2f(3.0f, 3.0));

            
            if (controller1.isButtonPressed(0, 2)){
                if (choicePos >= GutsPos) {
                    chosenChar1 = 2;
                    choicePos = 800;
                }
                else{}
            }
            if (controller1.isButtonPressed(0, 1)){
                if (choicePos <= ShadrPos) {
                    chosenChar1 = 1;
                    choicePos = 1100;
                }
                else{}
            }


            if (controller1.isButtonPressed(0, 7) && choicePos == GutsPos && !(chosenChar1 == 0)){
                music.stop();
                chosenChar1 = 1; // to load properly the sprites for now
                chosenChar2 = 2;
                launchGame(window, character, font, chosenChar1, chosenChar2); // Fix: Add missing argument for the launchGame function
            }
            else if (controller1.isButtonPressed(0, 7) && choicePos == ShadrPos && !(chosenChar1 == 0)){
                music.stop();
                chosenChar1 = 2; // to load properly the sprites for now
                chosenChar2 = 1;
                launchGame(window, character, font, chosenChar1, chosenChar2); // Fix: Add missing argument for the launchGame function
            }

            window.clear(sf::Color::Black);
            window.draw(s);
            window.draw(iconSquare);
            window.draw(iconSquare2);
            window.draw(iconGuts);
            window.draw(iconShadr);
            window.draw(choose);
            window.draw(ChooseCharacter);
            window.display();       
    }
    return;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pixel Showdown", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    sf::Music music;
    if (!music.openFromFile("Music/menu.wav")) {
        // handle error
    }
    music.stop();
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

    // Controller is connected
    sf::Joystick controller1;
    controller1.isConnected(0);

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

            // Check button presses and keyboard inputs
            if (controller1.isButtonPressed(0, 1) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (!wasZPressed) {
                    updateChoicePosition(choicePos, 100, playButtonPos, exitButtonPos);
                    wasZPressed = true;
                }
            } else {
                wasZPressed = false;
            }

            if (controller1.isButtonPressed (0,2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                if (!wasSPressed) {
                    updateChoicePosition(choicePos, -100, playButtonPos, exitButtonPos);
                    wasSPressed = true;
                }
            } else {
                wasSPressed = false;
            }

            if ((controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && choicePos == playButtonPos) { // checks if you're on the Play button
                music.stop();
                charSelection(window, font);
                return 0;
            }
            if ((controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && choicePos == howToPlayButtonPos) { // checks if you're on the How to Play button
                howToPlay(window, font);
            }
            if ((controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && choicePos == settingsButtonPos) { // checks if you're on the Settings button
                clickSound.play();
            }
            if ((controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && choicePos == exitButtonPos) { // checks if you're on the Exit button
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
