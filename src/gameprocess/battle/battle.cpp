#include "battle.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"
#include "../../controller/enviroment.h"

#include<iostream>

// add your code to implement the Battle class here
Battle::Battle(Player* p, Enemy* e):player(p), enemy(e), state(ACTION_SELECTING) {

}

Battle::~Battle() = default;

ProcessInfo Battle::run(InputState s) {

    switch(state) {
    case ACTION_SELECTING: {
        damageToPlayer=0, damageToEnemy=0, damageDealt=false;
        switch(s) {
            case ACTION_DOWN:
                actionPlayerSelected=(BattleAction)((actionPlayerSelected+1)%BattleActionCount);
                break;
            case ACTION_UP:
                actionPlayerSelected=(BattleAction)((actionPlayerSelected-1+BattleActionCount)%BattleActionCount);
                break;
            case ACTION_CONFIRM:
                actionEnemySelected=(BattleAction)(rand()%3);
                damageToEnemy = damageCalculate(actionPlayerSelected, actionEnemySelected, player->getAttack());
                damageToPlayer = damageCalculate(actionEnemySelected, actionPlayerSelected, enemy->getAttack());
                state=TURN_END;
            default:
                break;
        }
        return CONTINUE;
    }
    case TURN_END: {

        if(!damageDealt) {
            player->health-=damageToPlayer;
            enemy->health-=damageToEnemy;
            if(actionPlayerSelected==HEAL)
                player->health+=player->getHealPower();
            if(player->health>player->getMaxHealth())
                player->health=player->getMaxHealth();
            damageDealt=true;
        }
        if(s==ACTION_CONFIRM) {

            if(player->health<=0) {
                state=PLAYER_DEAD;
                return CONTINUE;
            }
            if(enemy->health<=0) {
                state=ENEMY_DEAD;
                return CONTINUE;
            }
            state=ACTION_SELECTING;
            return CONTINUE;
        } else {


            return CONTINUE;
        }
        break;
    }
    default:

        if(s==ACTION_CONFIRM)
            if(state==PLAYER_DEAD) return BATTLE_FINISH_PLAYER_DEAD;
            else /*if(state==ENEMY_DEAD)*/ return BATTLE_FINISH_PLAYER_WIN;
        else {

            return CONTINUE;
        }
        break;
    }
}

int Battle::damageCalculate(BattleAction attackerAction, BattleAction targetAction, int damage) {
    int res=0;
    switch(attackerAction) {
        case FORCE_ATTACK:
            res=damage*FORCE_ATTACK_MULTIPLIER;
            break;
        case ATTACK:
            res=damage*ATTACK_MULTIPLIER;
            break;
        case DEFEND:
        case HEAL:
            break;
        default:
            break;
    }
    switch(targetAction) {
        case DEFEND:
            res/=DEFEND_MULTIPLIER;
            break;
        case FORCE_ATTACK:
        case HEAL:
            res*=FORCE_ATTACK_MULTIPLIER;
            break;
        default:
            break;
    }
    return res;
}
















std::string Battle::BattleActionToString(BattleAction action) {
    switch(action) {
        case FORCE_ATTACK:
            return "force attack";
        case ATTACK:
            return "attack";
        case DEFEND:
            return "defend";
        case HEAL:
            return "heal";
        default:
            return "none";
    }
}

std::string repeat(const std::string& input, unsigned num) {
    std::string s;
    s.reserve(input.size() * num);
    while (num--) s += input;
    return s;
}

void Battle::render() {

    // remember screen size is defined in controller/enviroment.h

    // line 1
    AnsiPrint("\n", black, black);

    // life bar and name
    const int windowEdge = 1;
    const int lifeBarWidth = GAME_WINDOW_SIZE_X - windowEdge * 2; // 2 means left and right edge

    int playerHealthBlocks = (int) double(std::max(player->getHealth(),0)) / double(player->getMaxHealth()) * lifeBarWidth;
    int enemyHealthBlocks = (int) double(std::max(enemy->getHealth(),0)) / double(enemy->getMaxHealth()) * lifeBarWidth;



    std::string playerLifeBar = repeat("██", playerHealthBlocks) + repeat("__", (lifeBarWidth - playerHealthBlocks));
    std::string enemyLifeBar = repeat("__", (lifeBarWidth - enemyHealthBlocks)) + repeat("██", enemyHealthBlocks);

    // line 2
    AnsiPrint("  ", black, black);
    AnsiPrint(playerLifeBar.c_str(), blue, black);
    AnsiPrint("\n", black, black);


    // line 3
    AnsiPrint("  ", black, black);
    AnsiPrint(player->getName().c_str(), blue, black);
    AnsiPrint("\n", black, black);

    // line 4
    AnsiPrint("  ", black, black);
    AnsiPrint(std::string((GAME_WINDOW_SIZE_X - windowEdge * 2) * GAME_WINDOW_ONEBLOCK_WIDTH - enemy->getName().size(), ' ').c_str(), black, black);
    AnsiPrint(enemy->getName().c_str(), red, black);
    AnsiPrint("\n", black, black);

    // line 5
    AnsiPrint("  ", black, black);
    AnsiPrint(enemyLifeBar.c_str(), red, black);
    AnsiPrint("\n", black, black);

    // line 6~12
    AnsiPrint("\n\n\n\n\n\n\n", black, black);

    switch (state) {
        case ACTION_SELECTING: {

            // line 13 ~ 20
            AnsiPrint("  Please select your action:\n\n", white, black);
            AnsiPrint("    1) Force Attack\n", (actionPlayerSelected == FORCE_ATTACK ? yellow : white), black);
            AnsiPrint("    2) Attack\n", (actionPlayerSelected == ATTACK ? yellow : white), black);
            AnsiPrint("    3) Defend\n", (actionPlayerSelected == DEFEND ? yellow : white), black);
            AnsiPrint("    4) Heal\n\n", (actionPlayerSelected == HEAL ? yellow : white), black);
            AnsiPrint("  Press Enter to confirm.\n\n", white, black);

            break;
        }

        case TURN_END: {
            // line 13
            AnsiPrint("  You ", blue, black);
            AnsiPrint("performed the ", white, black);
            AnsiPrint(BattleActionToString(actionPlayerSelected).c_str(), yellow, black);
            AnsiPrint(" on the ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint(".\n", white, black);

            // line 14 15
            AnsiPrint("  ", black, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint(" performed the ", white, black);
            AnsiPrint(BattleActionToString(actionEnemySelected).c_str(), yellow, black);
            AnsiPrint(" on ", white, black);
            AnsiPrint("You", blue, black);
            AnsiPrint(".\n\n", white, black);

            // line 16
            AnsiPrint("  You ", blue, black);
            AnsiPrint("dealt ", white, black);
            AnsiPrint(std::to_string(damageToEnemy).c_str(), yellow, black);
            AnsiPrint(" damage to ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint(".\n", white, black);

            // line 17 18
            AnsiPrint("  Enemy ", red, black);
            AnsiPrint("dealt ", white, black);
            AnsiPrint(std::to_string(damageToPlayer).c_str(), yellow, black);
            AnsiPrint(" damage to ", white, black);
            AnsiPrint("You", blue, black);
            AnsiPrint(".\n\n", white, black);

            // line 19 20
            AnsiPrint("  Press any key to continue.\n\n", white, black);
            break;
        }

        case ENEMY_DEAD: {
            // line 13
            AnsiPrint("  You ", blue, black);
            AnsiPrint("defeated ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint("!\n", blue, black);

            // line 14 ~ 20
            AnsiPrint("\n\n\n\n\n\n\n", black, black);
            break;
        }

        case PLAYER_DEAD: {
            // line 13
            AnsiPrint("  You ", red, black);
            AnsiPrint("were defeated by ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint("!\n", red, black);

            // line 14 ~ 20
            AnsiPrint("\n\n\n\n\n\n\n", black, black);
            break;
        }
    }

}
