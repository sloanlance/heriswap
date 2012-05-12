#pragma once

#include "states/GameStateManager.h"
#include "modes/GameModeManager.h"
#include "AnimedEntity.h"


class MainMenuGameStateManager : public GameStateManager {
	public:
		MainMenuGameStateManager(LocalizeAPI* lAPI) : localizeAPI(lAPI) { };
		~MainMenuGameStateManager();
		void Setup();
		void Enter();
		GameState Update(float dt);
		void Exit();

		GameMode choosenGameMode;
		Entity eStart[2];
		Entity menufg, menubg;
		AnimatedActor* herisson;

	private:
		Entity bStart[2];
		Entity modeTitleToReset;
		LocalizeAPI* localizeAPI;
};
