#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
int main(){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "test", sf::Style::None);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
    if (sf::joystick::isConnected(1)) {
        // Check button presses
        for (int button = 0; button < sf::joystick::ButtonCount; ++button) {
            if (sf::joystick::isButtonPressed(1, button)) {
                std::cout << "Button " << button << " is pressed." << std::endl;
            }
        }
    }
    else {
        std::cout << "Controller is not connected." << std::endl;
    }
    }
}
}