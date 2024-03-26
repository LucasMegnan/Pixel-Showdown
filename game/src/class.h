#include "sheet.h"

class Character
{
public:
    int chosenChar; // 1 for Guts, 2 for Shadr...

    float velocity; // speed
    bool isCrouch; // crouch condition
    bool cannotMove;
    bool isDie; // death condition
    bool lastDirectionLeft; // direction condition

    // HP management
    int HP;
    int maxHP;

    // attack management
    // int attackDamage;
    // bool isAttacking;
    // sf::FloatRect attackBounds;
    // sf::FloatRect bounds;

    // jump parameters
    int jumps;
    bool isZPressed;
    bool wasZPressed;
    bool isJumping;
    
    // dash parameters
    bool isDashing;
    float dashDirection;
    float dashDistance;

    // run parameters
    bool isRunning;
    bool isRunningL;

    // attack parameters
    bool isAttack1;
    bool isAttack2;
    bool isAttack3;
    bool isSpecial1;
    bool isSpecial2;
    bool isUlt;

};

