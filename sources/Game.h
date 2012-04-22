#pragma once
#include "GridSystem.h"
#include "GameState.h"

#define FAST 1.

class ScoreStorage {
	public:
		struct Score {
			int mode, points, level;
			float time;
			std::string name;
		};
		virtual bool initTable() = 0;
		virtual void submitScore(Score scr) = 0;
		virtual std::vector<Score> getScore(int mode) = 0;
		virtual bool request(std::string s, std::string* res) = 0;
		virtual bool soundEnable(bool switchIt) = 0;
		virtual void saveOpt(std::string opt, std::string name) = 0;
		virtual bool getName(std::string& result) = 0;
};

class PlayerNameInputUI {
	public:
		virtual void show() = 0;
		virtual bool query(std::string& result) = 0;

};

class PrivateData;
class Game {
	public:
		Game(NativeAssetLoader* loader, ScoreStorage* storage, PlayerNameInputUI* inputUI);
		void init(int windowW, int windowH, const uint8_t* in = 0, int size = 0);
		void tick(float dt);
		void togglePause(bool activate);
		void toggleShowCombi(bool forcedesactivate);
		void setMode();
		int saveState(uint8_t** out);

        void stateChanged(GameState from, GameState to);

		static Vector2 GridCoordsToPosition(int i, int j);
		static float CellSize();
		static float CellContentScale();
		static std::string cellTypeToTextureNameAndRotation(int type, float* rotation);
		static float cellTypeToRotation(int type);

	private:
		void loadFont(const std::string& name);
		void loadState(const uint8_t* in, int size);
		void bench(bool active, float updateDuration, float dt);

	PrivateData* datas;
	NativeAssetLoader* loader;
};
