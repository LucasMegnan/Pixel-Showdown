#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <SFML/Audio.hpp>

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

std::vector<sf::Texture> IdleGutsSheet = loadCharacterSheet("Imgs/Guts/Idle");
std::vector<sf::Texture> IdleLGutsSheet = loadCharacterSheet("Imgs/Guts/IdleL");
std::vector<sf::Texture> runGutsSheet = loadCharacterSheet("Imgs/Guts/Run");
std::vector<sf::Texture> runLGutsSheet = loadCharacterSheet("Imgs/Guts/RunL");
std::vector<sf::Texture> JMPGutsSheet = loadCharacterSheet("Imgs/Guts/Jmp");
std::vector<sf::Texture> JMPLGutsSheet = loadCharacterSheet("Imgs/Guts/JmpL");
std::vector<sf::Texture> CRHGutsSheet = loadCharacterSheet("Imgs/Guts/Crh");
std::vector<sf::Texture> CRHLGutsSheet = loadCharacterSheet("Imgs/Guts/CrhL");
std::vector<sf::Texture> ATTACKGutsSheet = loadCharacterSheet("Imgs/Guts/attack1");
std::vector<sf::Texture> ATTACKLGutsSheet = loadCharacterSheet("Imgs/Guts/attack1L");
std::vector<sf::Texture> ATTACK2GutsSheet = loadCharacterSheet("Imgs/Guts/attack2");
std::vector<sf::Texture> ATTACK2LGutsSheet = loadCharacterSheet("Imgs/Guts/attack2L");
std::vector<sf::Texture> ATTACK3GutsSheet = loadCharacterSheet("Imgs/Guts/attack3");
std::vector<sf::Texture> ATTACK3LGutsSheet = loadCharacterSheet("Imgs/Guts/attack3L");
std::vector<sf::Texture> SPECIALGutsSheet = loadCharacterSheet("Imgs/Guts/Special 1");
std::vector<sf::Texture> SPECIALLGutsSheet = loadCharacterSheet("Imgs/Guts/Special 1L");
std::vector<sf::Texture> SPECIAL2GutsSheet = loadCharacterSheet("Imgs/Guts/Special 2");
std::vector<sf::Texture> SPECIAL2LGutsSheet = loadCharacterSheet("Imgs/Guts/Special 2L");
std::vector<sf::Texture> DIEGutsSheet = loadCharacterSheet("Imgs/Guts/die");
std::vector<sf::Texture> DIELGutsSheet = loadCharacterSheet("Imgs/Guts/dieL");

// Loads player 2's sheet
std::vector<sf::Texture> IdleShadrSheet = loadCharacterSheet("Imgs/Shadr/Idle");
std::vector<sf::Texture> IdleLShadrSheet = loadCharacterSheet("Imgs/Shadr/IdleL");
std::vector<sf::Texture> RunShadrSheet = loadCharacterSheet("Imgs/Shadr/Run");
std::vector<sf::Texture> RunLShadrSheet = loadCharacterSheet("Imgs/Shadr/RunL");
std::vector<sf::Texture> CRHShadrSheet = loadCharacterSheet("Imgs/Shadr/Crh");
std::vector<sf::Texture> CRHLShadrSheet = loadCharacterSheet("Imgs/Shadr/CrhL");
std::vector<sf::Texture> JMPShadrSheet = loadCharacterSheet("Imgs/Shadr/Jmp");
std::vector<sf::Texture> JMPLShadrSheet = loadCharacterSheet("Imgs/Shadr/JmpL");
std::vector<sf::Texture> ATTACKShadrSheet = loadCharacterSheet("Imgs/Shadr/attack 1");
std::vector<sf::Texture> ATTACKLShadrSheet = loadCharacterSheet("Imgs/Shadr/attack 1L");
std::vector<sf::Texture> ATTACK2ShadrSheet = loadCharacterSheet("Imgs/Shadr/attack 2");
std::vector<sf::Texture> ATTACK2LShadrSheet = loadCharacterSheet("Imgs/Shadr/attack 2L");
std::vector<sf::Texture> SPECIALShadrSheet = loadCharacterSheet("Imgs/Shadr/Special 1"); 
std::vector<sf::Texture> SPECIALLShadrSheet = loadCharacterSheet("Imgs/Shadr/Special 1L"); 
std::vector<sf::Texture> SPECIAL2ShadrSheet = loadCharacterSheet("Imgs/Shadr/Special 2"); 
std::vector<sf::Texture> SPECIAL2LShadrSheet = loadCharacterSheet("Imgs/Shadr/Special 2L"); 
std::vector<sf::Texture> DIEShadrSheet = loadCharacterSheet("Imgs/Shadr/Die");
std::vector<sf::Texture> DIELShadrSheet = loadCharacterSheet("Imgs/Shadr/DieL");
