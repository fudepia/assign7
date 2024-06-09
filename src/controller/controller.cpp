#include <iostream>
#include<algorithm>

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
    currentProcess = new Move(player, rooms[currentRoomIndex]);
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
    switch(info) {
        case MOVE_FINISH_ROOMCHANGE_LEFT:
            --currentRoomIndex;
            if(currentRoomIndex<0) currentRoomIndex+=rooms.size();
            currentProcess = new Move(player, rooms[currentRoomIndex]);
            break;
        case MOVE_FINISH_ROOMCHANGE_RIGHT:
            ++currentRoomIndex;
            if((size_t)currentRoomIndex>=rooms.size()) currentRoomIndex-=rooms.size();
            currentProcess = new Move(player, rooms[currentRoomIndex]);
            break;
        case MOVE_FINISH_PAUSE:
            currentProcess = new Pause();
            break;
        case PAUSE_FINISH:
            currentProcess = new Move(player, rooms[currentRoomIndex]);
            break;
        case MOVE_FINISH_BATTLE:
            if(rooms[currentRoomIndex]->encounteredE!=nullptr)
            currentProcess = new Battle(player, rooms[currentRoomIndex]->encounteredE);
            break;
        case BATTLE_FINISH_PLAYER_WIN:
            if(rooms[currentRoomIndex]->encounteredE->isLastBoss()) {
                currentProcess = new GameClear();
                if(s==ACTION_CONFIRM) state=PROCESS_GAMECLEAR;
                break;
            }
            (rooms[currentRoomIndex]->getEnemies()).erase(std::remove((rooms[currentRoomIndex]->getEnemies()).begin(), (rooms[currentRoomIndex]->getEnemies()).end(), rooms[currentRoomIndex]->encounteredE), (rooms[currentRoomIndex]->getEnemies()).end());
            rooms[currentRoomIndex]->encounteredE=nullptr;
            currentProcess = new Move(player, rooms[currentRoomIndex]);
            break;
        case BATTLE_FINISH_PLAYER_DEAD:
            currentProcess = new GameOver();
            if(s==ACTION_CONFIRM) state=PROCESS_GAMEOVER;
            break;
        case CONTINUE:
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
