#include "FadeStateManager.h"

#include <base/TouchInputManager.h>
#include <base/EntityManager.h>

#include "systems/TransformationSystem.h"
#include "systems/RenderingSystem.h"
#include "systems/ADSRSystem.h"

#include "Game.h"
#include "DepthLayer.h"

FadeGameStateManager::FadeGameStateManager(FadeType fade, GameState whoAmI, GameState whoIsNext, GameStateManager* enter, GameStateManager* exitD):
	fading(fade), iAm(whoAmI), heIs(whoIsNext), timeout(0), enterDelegate(enter), exitDelegate(exitD) {
}

void FadeGameStateManager::Setup() {
	eFading = theEntityManager.CreateEntity();
	ADD_COMPONENT(eFading, Transformation);
	ADD_COMPONENT(eFading, Rendering);
	TRANSFORM(eFading)->position = Vector2(0,0);
	TRANSFORM(eFading)->size = Vector2(10,20);
	RENDERING(eFading)->hide = true;
	RENDERING(eFading)->color = Color(0,0,0);
	TRANSFORM(eFading)->z = DL_Fading;

	ADD_COMPONENT(eFading, ADSR);
	ADSR(eFading)->idleValue = 0;
	ADSR(eFading)->attackValue = 1.0;
	ADSR(eFading)->attackTiming = 0.2;
	ADSR(eFading)->decayTiming = 0;
	ADSR(eFading)->sustainValue = 1.0;
	ADSR(eFading)->releaseTiming = .2;
	ADSR(eFading)->attackMode = Quadratic;
}

static void updateColor(Entity eFading, FadeType fading) {
	float value = ADSR(eFading)->value;
	if (fading == FadeIn)
		RENDERING(eFading)->color.a = 1 - value;
	else
		RENDERING(eFading)->color.a = value;
}

void FadeGameStateManager::Enter() {
	stateActiveDuration = 0;
	LOGW("Fade type: %d", fading);
	RENDERING(eFading)->hide = false;
	ADSR(eFading)->active = true;

	accum = 0;
	updateColor(eFading, fading);
	
	if (enterDelegate)
		enterDelegate->Enter();
}

GameState FadeGameStateManager::Update(float dt) {
	stateActiveDuration += dt;
	updateColor(eFading, fading);
	if (theTouchInputManager.isTouched() && !theTouchInputManager.wasTouched()) {
		return heIs;
	}
	if (ADSR(eFading)->value == ADSR(eFading)->sustainValue) {
		accum += dt;
		if (accum >= timeout)
			return heIs;
		else
			return iAm;
	}
	return iAm;
}

void FadeGameStateManager::Exit() {
	LOGW("Duration : %.3f", stateActiveDuration);
	RENDERING(eFading)->hide = true;
	ADSR(eFading)->active = false;

    if (exitDelegate)
        exitDelegate->LateExit();
}
