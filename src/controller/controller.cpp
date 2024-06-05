#include <iostream>

#include "controller.h"
#include "../gameobjects/room/roomdata.h"
#include "../functions/position/position.h"
#include "../functions/AnsiPrint/AnsiPrint.h"

#include "../gameprocess/allgameprocess.h"

Controller::Controller() {
    const int defaultRoomIndex = 0;
    //RoomData roomData = ROOM_DATA[defaultRoomIndex];
    //Room *room = new Room(roomData);
    //rooms.insert(std::pair<int, Room *>(defaultRoomIndex, room));
    for(size_t i=0; i<ROOM_DATA_SZ; ++i) {
        RoomData roomData = ROOM_DATA[i];
        auto rPtr = new Room(roomData);
        rooms.insert({i, rPtr});
    }
    currentRoomIndex=defaultRoomIndex;

    state=PROCESS_MOVEMENT; //?
    player=new Player(rooms[defaultRoomIndex]->playerInitialPosition);
    currentProcess = new Move(player, rooms[defaultRoomIndex]); //?
}

Controller::~Controller() {
	delete player;
	for(const auto&[i,p]:rooms) delete p;
}

RunningState Controller::run(InputState s) {

    if(state == PROCESS_GAMEOVER) {
        return EXIT;
    }

    if(state == PROCESS_GAMECLEAR) {
        return EXIT;
    }

    ProcessInfo info = currentProcess->run(s);

    // add your code to implement process control


    switch (state) {
    case PROCESS_MOVEMENT: {
    switch(s) {
        case ACTION_NONE: {}break;
        case ACTION_UP:
        case ACTION_DOWN:
        case ACTION_LEFT:
        case ACTION_RIGHT: {
                               auto orig=player->getPosition();
                               switch(player->move(s,
                                           [&](Position pos) { return rooms[currentRoomIndex]->walkable(pos); } // check lambda
                                      )) {
                                   case MOVE:
                                       break;
                                   case LEFTROOM: {
                                        --currentRoomIndex;
                                        if(currentRoomIndex<0) currentRoomIndex+=rooms.size();
                                            player->setPosition(Position{34, player->getPosition().getY()});
                                                  } break;
                                   case RIGHTROOM: {
                                        ++currentRoomIndex;
                                        if((size_t)currentRoomIndex>=rooms.size()) currentRoomIndex-=rooms.size();
                                            std::cerr << "next\n"<<currentRoomIndex;
                                            player->setPosition(Position{0, player->getPosition().getY()});
                                                   } break;
                               }
                           }break;
        case ACTION_CONFIRM: {
                             }break;
        case ACTION_PAUSE: {
                           }break;
        case ACTION_EXIT: { return EXIT;
                          }break;
        case ACTION_INIT: {
                          }break;
    }
        // add your code to implement the enemy movement
    auto& room=rooms[currentRoomIndex];
        for(auto &i:room->getEnemies()) {
            auto newPos=i->nextPosition();
            if(!(newPos==i->getPosition()))
                if(room->walkable(newPos)) i->setPosition(newPos);
        }

        break;
    }

    default:
        break;
    }
    this->render();

    return PLAY;
}

// Add your code to implement the Controller class here.















// render
void Controller::render() {
    currentProcess->render();
    output();
}
