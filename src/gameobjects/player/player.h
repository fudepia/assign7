#ifndef PLAYER_H
#define PLAYER_H

#include "../../gamecore/gamestate.h"
#include "../gameobject.h"
#include "playerstate.h"

using namespace PlayerState;

class Player: public GameObject {
    int healPower = 8;
public:
    Player(Position initialPosition);
    ~Player();

    MoveState move(GameState::InputState s);
    template<typename F>
    MoveState move(GameState::InputState s, F check) {
        using namespace GameState;
        auto newPos=getPosition();
        auto ret = MOVE;
        switch(s) {
            case ACTION_UP: {
                                newPos.decrY();
                            }break;
            case ACTION_DOWN: {
                                  newPos.incrY();
                              }break;
            case ACTION_LEFT: {
                                  if(newPos.getX()==0) ret = LEFTROOM;
                                  newPos.decrX();
                              }break;
            case ACTION_RIGHT: {
                                   if(newPos.getX()==34) ret = RIGHTROOM;
                                   newPos.incrX();
                               }break;
            default: break;
        }
        // TODO: Check go-ability here
        if(check(newPos)) setPosition(newPos);
        return ret;
    }

    // To enhance gameplay, a player healing option has been added.
    void heal(int amount);
    int getHealPower();
    
    void render();
};

#endif
