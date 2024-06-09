#include "player.h"
#include "../../controller/enviroment.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"
#include<cassert>

using namespace PlayerState;

Player::Player(Position initialPosition): GameObject(initialPosition, 20, 2, "Player") {
}

// Add your code to implement the Player class here.
Player::~Player() = default;

MoveState Player::move(GameState::InputState s) {
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
    //if(check(newPos))
        setPosition(newPos);
	return ret;
}


int Player::getHealPower() { return healPower; }




// render
void Player::render() {
    AnsiPrint("PL", green, blue);
}

