#ifndef BATTLE_H
#define BATTLE_H

#include "../gameprocess.h"
#include "battlestate.h"

using namespace BattleState;

class Battle: public GameProcessBase {
private:
    Player* player;
    Enemy* enemy;

    BattlePhase state;

    BattleAction actionPlayerSelected=BattleAction(0);
    BattleAction actionEnemySelected=BattleAction(0);

    // Please store the damage calculation result in this variable. 
    // The damage will be displayed based on this variable when rendering.
    int damageToPlayer=0;
    int damageToEnemy=0;

    static int damageCalculate(BattleAction attackerAction, BattleAction targetAction, int damage);

    static std::string BattleActionToString(BattleAction action);
    
    bool damageDealt=false;
public:
    Battle(Player* player, Enemy* enemy);
    ~Battle();

    ProcessInfo run(InputState action);

    void render();
};

#endif
