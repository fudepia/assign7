#ifndef SLIME_H
#define SLIME_H

#include "../enemy.h"

class Slime: public Enemy {
public:
    Slime(Position initialPosition);
    ~Slime() override;
    
    // Complete the Slime class with reference to the Enemy class.
    Position nextPosition() override;
    void render() override;

    void move(GameState::InputState action) override;

    template<typename T>
    void move(GameState::InputState s, T f) {
        return;
        auto newPos=getPosition();
        switch(rand()%4) {
            case 0:
                newPos.incrX(); break;
            case 1:
                newPos.incrY(); break;
            case 2:
                newPos.decrX(); break;
            case 3:
                newPos.decrY(); break;
        }
        if(f(newPos)) setPosition(newPos);
        return;
    }


};

#endif
