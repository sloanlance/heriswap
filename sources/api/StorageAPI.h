/*
	This file is part of Heriswap.

	@author Soupe au Caillou - Pierre-Eric Pelloux-Prayer
	@author Soupe au Caillou - Gautier Pelloux-Prayer

	Heriswap is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, version 3.

	Heriswap is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Heriswap.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <string>
#include <vector>

class StorageAPI {
    public:
        struct Score {
           int points, level;
            float time;
            std::string name;
        };

        virtual void init() = 0;
        virtual void submitScore(Score scr, int mode, int diff) = 0;
        virtual std::vector<Score> savedScores(int mode, int difficulty) = 0;
        virtual bool soundEnable(bool switchIt) = 0;
        virtual int getGameCountBeforeNextAd() = 0;
        virtual void setGameCountBeforeNextAd(int c) = 0;
        virtual int getSavedGamePointsSum() = 0;
        virtual bool everyModesPlayed() = 0;
};
