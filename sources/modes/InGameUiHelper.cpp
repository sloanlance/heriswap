#include "InGameUiHelper.h"
#include "systems/TransformationSystem.h"
#include "systems/RenderingSystem.h"
#include "systems/TextRenderingSystem.h"
#include "systems/ContainerSystem.h"
#include "systems/SoundSystem.h"
#include "systems/ButtonSystem.h"
#include "../PlacementHelper.h"
#include "../DepthLayer.h"

InGameUiHelper::InGameUiHelper() : built(false) {

}

void InGameUiHelper::build() {
	if (built)
		return;

	smallLevel = theEntityManager.CreateEntity();
	ADD_COMPONENT(smallLevel, Transformation);
	TRANSFORM(smallLevel)->position = Vector2(PlacementHelper::GimpXToScreen(624), PlacementHelper::GimpYToScreen(188));
	TRANSFORM(smallLevel)->z = DL_Score;
	ADD_COMPONENT(smallLevel, TextRendering);
	TEXT_RENDERING(smallLevel)->color = Color(1, 1, 1);
	TEXT_RENDERING(smallLevel)->fontName = "typo";
	TEXT_RENDERING(smallLevel)->charSize = Vector2(PlacementHelper::GimpWidthToScreen(690-620), PlacementHelper::GimpHeightToScreen(232-150));
	TEXT_RENDERING(smallLevel)->positioning = TextRenderingComponent::LEFT;
	TEXT_RENDERING(smallLevel)->isANumber = true;

	pauseButton = theEntityManager.CreateEntity();
	ADD_COMPONENT(pauseButton, Transformation);
	TRANSFORM(pauseButton)->position = Vector2(PlacementHelper::GimpXToScreen(23), PlacementHelper::GimpYToScreen(1215));
	TRANSFORM(pauseButton)->z = DL_Score;
	ADD_COMPONENT(pauseButton, TextRendering);
	TEXT_RENDERING(pauseButton)->color = Color(3.0/255, 99.0/255, 71.0/255);
	TEXT_RENDERING(pauseButton)->text = "Pause";
	TEXT_RENDERING(pauseButton)->fontName = "typo";
	TEXT_RENDERING(pauseButton)->charSize = Vector2(PlacementHelper::GimpWidthToScreen(30), PlacementHelper::GimpHeightToScreen(30));
	TEXT_RENDERING(pauseButton)->positioning = TextRenderingComponent::LEFT;
	ADD_COMPONENT(pauseButton, Container);
	CONTAINER(pauseButton)->includeChildren = true;
	//CONTAINER(pauseButton)->entities.push_back(pauseButton);
	ADD_COMPONENT(pauseButton, Button);
	ADD_COMPONENT(pauseButton, Sound);
	SOUND(pauseButton)->type = SoundComponent::EFFECT;

	scoreProgress = theEntityManager.CreateEntity();
	ADD_COMPONENT(scoreProgress, Transformation);
	TRANSFORM(scoreProgress)->z = DL_Score;
	TRANSFORM(scoreProgress)->position = Vector2(0, PlacementHelper::GimpYToScreen(1215));
	ADD_COMPONENT(scoreProgress, TextRendering);
	TEXT_RENDERING(scoreProgress)->color = Color(3.0/255, 99.0/255, 71.0/255);
	TEXT_RENDERING(scoreProgress)->fontName = "typo";
	TEXT_RENDERING(scoreProgress)->charSize = Vector2(PlacementHelper::GimpWidthToScreen(47), PlacementHelper::GimpHeightToScreen(47));
	TEXT_RENDERING(scoreProgress)->positioning = TextRenderingComponent::CENTER;
	TEXT_RENDERING(scoreProgress)->isANumber = true;

	built = true;
}

void InGameUiHelper::show() {
	if (!built)
		return;

	TEXT_RENDERING(smallLevel)->hide = false;
	TEXT_RENDERING(pauseButton)->hide = false;
	TEXT_RENDERING(scoreProgress)->hide = false;
}

void InGameUiHelper::update(float dt) {
	// handle button
	if (BUTTON(pauseButton)->clicked) {
		SOUND(pauseButton)->sound = theSoundSystem.loadSoundFile("audio/click.wav", false);
		BUTTON(pauseButton)->clicked=false;
		game->togglePause(true);
	}
}

void InGameUiHelper::hide() {
	if (!built)
		return;
	TEXT_RENDERING(smallLevel)->hide = true;
	TEXT_RENDERING(pauseButton)->hide = true;
	TEXT_RENDERING(scoreProgress)->hide = true;
}

void InGameUiHelper::destroy() {
	if (!built)
		return;
	theEntityManager.DeleteEntity(smallLevel);
	theEntityManager.DeleteEntity(pauseButton);
	theEntityManager.DeleteEntity(scoreProgress);
}