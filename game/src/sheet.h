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

std::vector<sf::Texture> IdleCharacterSheet = loadCharacterSheet("Imgs/Characters/Idle");
std::vector<sf::Texture> IdleLCharacterSheet = loadCharacterSheet("Imgs/Characters/IdleL");
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

// Loads player 2's sheet
std::vector<sf::Texture> IdleCharacterSheet2 = loadCharacterSheet("Imgs/Characters 2/Idle");
std::vector<sf::Texture> IdleLCharacterSheet2 = loadCharacterSheet("Imgs/Characters 2/IdleL");
std::vector<sf::Texture> RunCharacterSheet2 = loadCharacterSheet("Imgs/Characters 2/Run");
std::vector<sf::Texture> RunLCharacterSheet2 = loadCharacterSheet("Imgs/Characters 2/RunL");
std::vector<sf::Texture> CRHCharecterSheet2 = loadCharacterSheet("Imgs/Characters 2/Crh");
std::vector<sf::Texture> CRHLCharecterSheet2 = loadCharacterSheet("Imgs/Characters 2/CrhL");
std::vector<sf::Texture> JMPCharecterSheet2 = loadCharacterSheet("Imgs/Characters 2/Jmp");
std::vector<sf::Texture> JMPLCharecterSheet2 = loadCharacterSheet("Imgs/Characters 2/JmpL");
std::vector<sf::Texture> ATTACKCharecterSheet2 = loadCharacterSheet("Imgs/Characters 2/attack 1");
std::vector<sf::Texture> ATTACKLCharecterSheet2 = loadCharacterSheet("Imgs/Characters 2/attack 1L");
std::vector<sf::Texture> ATTACK2CharecterSheet2 = loadCharacterSheet("Imgs/Characters 2/attack 2");
std::vector<sf::Texture> ATTACK2LCharecterSheet2 = loadCharacterSheet("Imgs/Characters 2/attack 2L");
std::vector<sf::Texture> DIECharecterSheet2 = loadCharacterSheet("Imgs/Characters 2/die");
