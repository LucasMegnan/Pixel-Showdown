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
    if (sf::Joystick::isConnected(1)) {
        // Check button presses
        for (int button = 0; button < sf::Joystick::ButtonCount; ++button) {
            if (sf::Joystick::isButtonPressed(1, button)) {
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