#pragma once

#include "base/EntityManager.h"

#include "systems/TransformationSystem.h"
#include "systems/RenderingSystem.h"
#include "systems/ADSRSystem.h"

#include "states/GameStateManager.h"
#include "GridSystem.h"
#include "Game.h"
#include "modes/GameModeManager.h"

class DeleteGameStateManager : public GameStateManager {
	public:

		DeleteGameStateManager(SuccessAPI* successAPI);
		~DeleteGameStateManager();
		void Setup();
		void Enter();
		GameState Update(float dt);
		void Exit();

		void setAnimSpeed();
	private:

		// datas
		Entity eRemove;
		std::vector<Combinais> removing;
        std::vector<Entity> littleLeavesDeleted;
        SuccessAPI* successAPI;
};
