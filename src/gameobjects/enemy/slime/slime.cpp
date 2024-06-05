#include "slime.h"
#include <stdlib.h>

#include "../../../functions/AnsiPrint/AnsiPrint.h"

Slime::Slime(Position initialPosition): Enemy(initialPosition, 5, 1, "Slime") {}

// add your code to implement the Slime class here

Slime::~Slime() = default;

Position Slime::nextPosition() {
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
    return newPos;
}












// render function

void Slime::render() {
    AnsiPrint("==", yellow, green);
}
