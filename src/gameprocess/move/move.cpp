#include "move.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"
#include "../../controller/enviroment.h"
#include<iostream>

// Move the code from controller.cpp to this file, completing the Move Class

Move::Move(Player* p, Room* r): player(p), room(r) {}
Move::~Move() {}
// not assuming ownership

ProcessInfo Move::run(InputState s) {
    if(s==ACTION_PAUSE) return MOVE_FINISH_PAUSE;

    auto checkWalkable= [&](Position pos) { return room->walkable(pos); }; // check lambda
    //player
    auto orig=player->getPosition();
    switch(player->move(s, checkWalkable)) {
        case MOVE:
            break;
        case LEFTROOM:
            player->setPosition(Position{34, player->getPosition().getY()});
            return MOVE_FINISH_ROOMCHANGE_LEFT;
            break;
        case RIGHTROOM:
            player->setPosition(Position{0, player->getPosition().getY()});
            return MOVE_FINISH_ROOMCHANGE_RIGHT;
            break;
    }
    // add your code to implement the enemy movement
    for(auto &i:room->getEnemies()) {
        std::cerr << "Updating..."<<i<<std::endl;
        //i->move(s, checkWalkable);
        if(player->getPosition()==i->getPosition()) {
            room->encounteredE=i;
            return MOVE_FINISH_BATTLE;
        }
        auto newPos=i->nextPosition();
        if(!(newPos==i->getPosition()))
            if(room->walkable(newPos)) i->setPosition(newPos);
        if(player->getPosition()==i->getPosition()) {
            room->encounteredE=i;
            return MOVE_FINISH_BATTLE;
        }
    }
    return CONTINUE;
}



void Move::render() {
    for (int y = 0; y < GAME_WINDOW_SIZE_Y; y++) {
        for (int x = 0; x < GAME_WINDOW_SIZE_X; x++) {
            if(player->getPosition() == Position(x, y)) {
                player->render();
                continue;
            }
            bool flag = false;
            for(auto enemy : room->getEnemies()) {
                if(enemy->getPosition() == Position(x, y)) {
                    enemy->render();
                    flag = true;
                    continue;
                }
            }
            if(flag) continue;
            room->render(Position(x, y));
        }
        AnsiPrint("\n", nochange, nochange);
    }
}
