#include "sheet.h"

class Character
{
public:
    float velocity; // speed
    bool isCrouch; // crouch condition
    bool cannotMove;
    bool isDie; // death condition
    bool lastDirectionLeft; // direction condition

    // HP management
    int HP;
    int maxHP;

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
    
};

