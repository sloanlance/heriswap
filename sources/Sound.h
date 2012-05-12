#pragma once
#include "base/Log.h"
#include <vector>

struct Canal {
	Canal() {
		timeLoop = 17.;
		musicLength=18.;
		indice = 0;
		multipleStrings=false;
	}
	void stop() {
		SOUND(sounds[0])->stop = true;
		SOUND(sounds[1])->stop = true;
		if (multipleStrings) name = "";
		indice=0;
	}

	bool update(float dt) {
		SOUND(sounds[0])->stop = false;
		SOUND(sounds[1])->stop = false;
		if (SOUND(sounds[indice])->sound == InvalidSoundRef && !name.empty()) {
			SOUND(sounds[indice])->sound = theSoundSystem.loadSoundFile(name, true);
			if (multipleStrings) name = "";
		}
		// +dt is magic!
		float t = SOUND(sounds[indice])->position * musicLength;// + dt;
		if (t >= timeLoop) {
			int old = indice;
			indice = (indice+1)%2;
			if (!name.empty()) {
				SOUND(sounds[indice])->sound = theSoundSystem.loadSoundFile(name, true);
				SOUND(sounds[indice])->masterTrack = SOUND(sounds[old]);
				SOUND(sounds[indice])->masterTrackOffsetMs = -timeLoop * 1000;
			}
		}
		return (SOUND(sounds[indice])->sound == InvalidSoundRef);
	}
	bool multipleStrings;
	float timeLoop, musicLength;
	int indice;
	Entity* sounds;
	std::string name;
};

std::vector<std::string> newMusics(std::vector<std::string> &old);
bool updateMusic(Canal* canal, Canal* canalStress1, Canal* canalStress2, float percentDone, float dt);
