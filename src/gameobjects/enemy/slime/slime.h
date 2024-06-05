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









};

#endif
