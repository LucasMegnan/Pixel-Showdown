#include "sheet.h"

class Character
{
public:
    int chosenChar; // 1 for Guts, 2 for Shadr...

    float velocity; // speed
    bool isCrouch; // crouch condition
    bool isProtect;
    bool isDie; // death condition
    bool lastDirectionLeft; // direction condition
    int lives = 3;

    // HP management
    float HP;
    float maxHP;

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

    // attack management
    float attackDamage;

    // attack parameters
    bool isAttack1;
    bool isAttack2;
    bool isSpecial1;
    bool isSpecial2;
    
    // cooldowns
    float attackCooldown = 0.5f;
    float special1Cooldown;
    float special2Cooldown;
    float dashCooldown = 3.5f;

};

