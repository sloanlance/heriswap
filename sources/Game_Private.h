#pragma once

#include "base/EntityManager.h"
#include "systems/SoundSystem.h"
#include "Sound.h"
class Game;
class ScoreStorage;
class PlayerNameInputUI;
class GameStateManager;
#include "modes/GameModeManager.h"

#include <map>
class PrivateData {
    public:
        PrivateData(Game* game, ScoreStorage* storagee, PlayerNameInputUI* inputUI);

        void Setup(int windowW, int windowH);

     //bench data
     std::map<std::string, Entity> benchTimeSystem;
     Entity benchTotalTime, targetTime;

     GameState state, stateBeforePause;
     bool stateBeforePauseNeedEnter;
     Entity logo, logo_bg, sky, decord2nd, decord1er;
     std::map<GameState, GameStateManager*> state2Manager;
     std::map<GameMode, GameModeManager*> mode2Manager;
     ScoreStorage* storage;
     GameMode mode;

     Entity cursor;

     Entity soundButton;
     Canal canalMenu, canalStress1, canalStress2, canal[4];
     Entity musicMenu[2], musicStress1[2], musicStress2[2], music[8];
};