#include "Platformer.h"

bool wasZPressed = false;
bool wasSPressed = false;
bool wasSpacePressed = false;
bool wasButton0Pressed = false;
bool wasButton3Pressed = false;
bool musicOn = true;

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

bool settings(sf::RenderWindow& window, sf::Font font, bool musicOn){
    sf::Texture t;
    t.loadFromFile("imgs/bg2.png");
    sf::Sprite s(t);

    sf::Text settingsText("Settings", font);
    settingsText.setPosition(300, 75);
    settingsText.setFillColor(sf::Color::Yellow);
    settingsText.setScale(4, 4);

    sf::Text musicSettingOn("Music:\tOn\t\t\t\tPress X or B to change", font);
    musicSettingOn.setPosition(700, 300);
    musicSettingOn.setFillColor(sf::Color::Blue);
    musicSettingOn.setScale(1.5, 1.5);
    sf::Text musicSettingOff("Music:\tOff\t\t\t\tPress X or B to change", font);
    musicSettingOff.setPosition(700, 300);
    musicSettingOff.setFillColor(sf::Color::Blue);
    musicSettingOff.setScale(1.5, 1.5);

    sf::Text Return("Press Select to return", font);
    Return.setPosition(775, 900);
    Return.setFillColor(sf::Color::Yellow);
    Return.setScale(1.5, 1.5);

    const float JoystickSensitivity = 5.0f;
    const float JoystickNeutralThreshold = 7.5f;
    float prevX = 0.0f;

    sf::Joystick controller1;

    while (window.isOpen())
    {
        float currentX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
            controller1.update();

            if (controller1.isButtonPressed(0, 6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                return musicOn;
            }
            if (std::abs(currentX - prevX) > JoystickSensitivity){ 
                if ((currentX > JoystickNeutralThreshold) && musicOn == true){ // right
                    musicOn = false;
                 }
                if ((currentX < -JoystickNeutralThreshold) && musicOn == false){ // left
                    musicOn = true;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                if (!wasSpacePressed) {
                    musicOn = !musicOn;
                    wasSpacePressed = true;
                }
            }
            
        window.clear(sf::Color::Black);
        window.draw(s);
        window.draw(settingsText);
        if (musicOn == true){
            window.draw(musicSettingOn);
        }
        else {
            window.draw(musicSettingOff);
        }
        window.draw(Return);
        window.display();

    }
    return musicOn;
}

void howToPlay(sf::RenderWindow& window, sf::Font font){
    sf::Texture t;
    t.loadFromFile("imgs/bg2.png");
    sf::Sprite s(t);

    sf::Text howToPlayText("How to play?", font);
    howToPlayText.setPosition(700, 75);
    howToPlayText.setFillColor(sf::Color::Yellow);
    howToPlayText.setScale(4, 4);

    sf::Text instructions("Joystick  to move\nClick Joystick  to protect\nA  to jump\nB  to dash\nX-Y  to attack\nLB-RB  to special", font);
    instructions.setPosition(700, 300);
    instructions.setFillColor(sf::Color::Blue);
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

            if (controller1.isButtonPressed(0, 6) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                return;
            }
            
        window.clear(sf::Color::Black);
        window.draw(s);
        window.draw(howToPlayText);
        window.draw(instructions);
        window.draw(Return);
        window.display();

    }
    return;
}

void charSelection (sf::RenderWindow& window, sf::Font font, int musicOn){
    sf::Music music;
    if (!music.openFromFile("Music/charSelection.wav")) {
        // handle error
    }
    music.setLoop(true); // to loop the music

    Character firstPlayer;
    Character secondPlayer;

    sf::Text ChooseCharacter ("Choose your Character", font);
    ChooseCharacter.setPosition(600, 150);
    ChooseCharacter.setFillColor(sf::Color::Magenta);
    ChooseCharacter.setScale(3, 3);

    sf::Text CharacterName1 ("Guts", font);
    CharacterName1.setPosition(740, 725);
    CharacterName1.setFillColor(sf::Color::Magenta);
    CharacterName1.setScale(2, 2);

    sf::Text CharacterName2 ("Shadr", font);
    CharacterName2.setPosition(1055, 725);
    CharacterName2.setFillColor(sf::Color::Magenta);
    CharacterName2.setScale(2, 2);

    sf::Texture t;
    t.loadFromFile("imgs/bg2.png");
    sf::Sprite s(t);

    sf::RectangleShape iconSquare(sf::Vector2f(125.0f, 125.0f));
    iconSquare.setFillColor(sf::Color::Magenta);
    iconSquare.setPosition(725, 800); 
    
    sf::RectangleShape iconSquare2(sf::Vector2f(125.0f, 125.0f));
    iconSquare2.setFillColor(sf::Color::Magenta);
    iconSquare2.setPosition(1040, 800); 

    sf::Sprite iconGuts;
    sf::Sprite iconShadr;
    sf::Sprite choose1;
    sf::Sprite choose2;

    sf::Texture charIconGuts;
    charIconGuts.loadFromFile("Imgs/Guts/icon.png");
    sf::Texture charIconShadr;
    charIconShadr.loadFromFile("Imgs/Shadr/icon.png");
    sf::Texture charChoose1;
    charChoose1.loadFromFile("Imgs/selectHand1.png");
    sf::Texture charChoose2;
    charChoose2.loadFromFile("Imgs/selectHand2.png");

    int character;
    int GutsPos = 800;
    int ShadrPos = 1100;
    int choicePos1 = 950;
    int choicePos2 = 950;

    iconGuts.setPosition(700, 815);
    iconGuts.setTexture(charIconGuts);
    iconGuts.setScale(sf::Vector2f(3.0f, 3.0));
    iconShadr.setPosition(1050, 815);
    iconShadr.setTexture(charIconShadr);
    iconShadr.setScale(sf::Vector2f(3.3f, 3.3));

    int chosenChar1 = 0;
    int chosenChar2 = 0;

    const float JoystickSensitivity = 5.0f;
    const float JoystickSensitivity2 = 5.0f;
    const float JoystickNeutralThreshold = 7.5f;
    const float JoystickNeutralThreshold2 = 7.5f;
    float prevX = 0.0f;
    float prevX2 = 0.0f;

    sf::Joystick controller1;
    sf::Joystick controller2;

    while (window.isOpen())
    {
        float currentX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float currentX2 = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

            if (musicOn == true){
                if (music.getStatus() != music.Playing){
                    music.play();
                }
                else{
                }
            }
            else{
                music.stop();
            }

            choose1.setPosition(choicePos1, 800);
            choose1.setTexture(charChoose1);
            choose1.setScale(sf::Vector2f(3.0f, 3.0));
            choose2.setPosition(choicePos2, 850);
            choose2.setTexture(charChoose2);
            choose2.setScale(sf::Vector2f(3.0f, 3.0));


            
            if ((std::abs(currentX - prevX) > JoystickSensitivity && currentX < -JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                if (choicePos1 >= GutsPos) {
                    chosenChar1 = 2;
                    choicePos1 = 800;
                }
                else{}
            }
            if ((std::abs(currentX - prevX) > JoystickSensitivity && currentX > JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                if (choicePos1 <= ShadrPos) {
                    chosenChar1 = 1;
                    choicePos1 = 1100;
                }
                else{}
            }
            if ((std::abs(currentX2 - prevX2) > JoystickSensitivity2 && currentX2 < -JoystickNeutralThreshold2) || sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                if (choicePos2 >= GutsPos) {
                    chosenChar2 = 1;
                    choicePos2 = 800;
                }
                else{}
            }
            if ((std::abs(currentX2 - prevX2) > JoystickSensitivity2 && currentX2 > JoystickNeutralThreshold2) || sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
                if (choicePos2 <= ShadrPos) {
                    chosenChar2 = 2;
                    choicePos2 = 1100;
                }
                else{}
            }


            if ((controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && !chosenChar1 == 0 && !chosenChar2 == 0){
                if (choicePos1 == GutsPos){
                    music.stop();
                    chosenChar1 = 1;
                    launchGame(window, character, font, musicOn, chosenChar1, chosenChar2, firstPlayer, secondPlayer);
                }
                else if (choicePos1 == ShadrPos){
                    music.stop();
                    chosenChar1 = 2; 
                    launchGame(window, character, font, musicOn, chosenChar1, chosenChar2, firstPlayer, secondPlayer);
                }
            }
            else if ((controller2.isButtonPressed(1, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && !chosenChar1 == 0 && !chosenChar2 == 0){
                if (choicePos2 == GutsPos){
                    music.stop();
                    chosenChar2 = 1;
                    launchGame(window, character, font, musicOn, chosenChar1, chosenChar2, firstPlayer, secondPlayer);
                }
                else if (choicePos2 == ShadrPos){
                    music.stop();
                    chosenChar2 = 2; 
                    launchGame(window, character, font, musicOn, chosenChar1, chosenChar2, firstPlayer, secondPlayer);
                }
            }

            window.clear(sf::Color::Black);
            window.draw(s);
            window.draw(iconSquare);
            window.draw(iconSquare2);
            window.draw(iconGuts);
            window.draw(iconShadr);
            window.draw(choose1);
            window.draw(choose2);
            window.draw(ChooseCharacter);
            window.draw(CharacterName1);
            window.draw(CharacterName2);
            window.display();       
    }
    return;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pixel Showdown", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    sf::Texture t;
    t.loadFromFile("imgs/bg2.png");
    sf::Sprite s(t);

    sf::Music music;
    if (!music.openFromFile("Music/menu.wav")) {
        // handle error
    }
    music.stop();
    music.setLoop(true); // to loop the music
    music.play();


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

    const float JoystickSensitivity = 7.5f;
    const float JoystickNeutralThreshold = 7.5f;
    float prevY = 0.0f;

    sf::Joystick controller1;

    while (window.isOpen())
    {
        float currentY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (musicOn == true){
                if (music.getStatus() != music.Playing){
                    music.play();
                }
                else{
                }
            }
            else{
                music.stop();
            }

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
            if ((std::abs(currentY - prevY) > JoystickSensitivity && currentY > JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (!wasButton3Pressed && !wasSPressed) {
                    updateChoicePosition(choicePos, 100, playButtonPos, exitButtonPos);
                    wasButton3Pressed = true;
                    wasSPressed = true;
                }
            } else {
                wasButton3Pressed = false;
                wasSPressed = false;
            }

            if ((std::abs(currentY - prevY) > JoystickSensitivity && currentY < -JoystickNeutralThreshold) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                if (!wasButton0Pressed && !wasZPressed) {
                    updateChoicePosition(choicePos, -100, playButtonPos, exitButtonPos);
                    wasButton0Pressed = true;
                    wasZPressed = true;
                }
            } else {
                wasButton0Pressed = false;
                wasZPressed = false;
            }

            if ((controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && choicePos == playButtonPos) { // checks if you're on the Play button
                music.stop();
                charSelection(window, font, musicOn);
                return 0;
            }
            if ((controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && choicePos == howToPlayButtonPos) { // checks if you're on the How to Play button
                howToPlay(window, font);
            }
            if ((controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && choicePos == settingsButtonPos) { // checks if you're on the Settings button
                if (settings(window, font, musicOn) == true){
                    musicOn = true;
                }
                else{
                    musicOn = false;
                }
            }
            if ((controller1.isButtonPressed(0, 7) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && choicePos == exitButtonPos) { // checks if you're on the Exit button
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(s);
        window.draw(Title);
        window.draw(playButton);
        window.draw(howToPlayButton);
        window.draw(settingsButton);
        window.draw(exitButton);
        window.display();
    }

    return 0;
}
