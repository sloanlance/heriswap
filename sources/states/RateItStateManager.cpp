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
#include "RateItStateManager.h"

#include <base/EntityManager.h>
#include <base/TouchInputManager.h>
#include <base/PlacementHelper.h>

#include "systems/ButtonSystem.h"
#include "systems/TextRenderingSystem.h"
#include "systems/MorphingSystem.h"
#include "systems/TransformationSystem.h"
#include "systems/RenderingSystem.h"
#include "systems/ContainerSystem.h"
#include "systems/SoundSystem.h"

#include "DepthLayer.h"

void RateItStateManager::Setup() {
	Color green = Color(3.0/255.0, 99.0/255, 71.0/255);

	//Creating text entities
	for (int i = 0; i < 3; i++) {
		bouton[i] = theTextRenderingSystem.CreateEntity();

		TRANSFORM(bouton[i])->z = DL_MainMenuUITxt;
		TEXT_RENDERING(bouton[i])->hide = true;
		TEXT_RENDERING(bouton[i])->positioning = TextRenderingComponent::LEFT;
		TEXT_RENDERING(bouton[i])->color = green;
		TEXT_RENDERING(bouton[i])->charHeight = PlacementHelper::GimpHeightToScreen(75);
		ADD_COMPONENT(bouton[i], Morphing);
	    TypedMorphElement<float>* sizeMorph = new TypedMorphElement<float>(&TEXT_RENDERING(bouton[i])->charHeight, TEXT_RENDERING(bouton[i])->charHeight, PlacementHelper::GimpHeightToScreen(54));
	    MORPHING(bouton[i])->elements.push_back(sizeMorph);
	    MORPHING(bouton[i])->timing = 0.2;

	    boutonContainer[i] = theEntityManager.CreateEntity();
	    ADD_COMPONENT(boutonContainer[i], Transformation);
	    TRANSFORM(boutonContainer[i])->size = Vector2(PlacementHelper::GimpWidthToScreen(708), PlacementHelper::GimpHeightToScreen(147));
	    TRANSFORM(boutonContainer[i])->position.X = 0;
	    TRANSFORM(boutonContainer[i])->z = DL_MainMenuUIBg;
	    ADD_COMPONENT(boutonContainer[i], Rendering);
	    RENDERING(boutonContainer[i])->texture = theRenderingSystem.loadTextureFile("fond_bouton");
	    RENDERING(boutonContainer[i])->color.a = 0.5;


		TEXT_RENDERING(bouton[i])->charHeight = PlacementHelper::GimpHeightToScreen(54);
		TEXT_RENDERING(bouton[i])->charHeight = PlacementHelper::GimpHeightToScreen(75);
		ADD_COMPONENT(boutonContainer[i], Sound);
		ADD_COMPONENT(boutonContainer[i], Button);
		BUTTON(boutonContainer[i])->enabled = false;

	}
	TEXT_RENDERING(bouton[0])->text = localizeAPI->text("mode_1", "Rate it");
	TRANSFORM(bouton[0])->position.X = PlacementHelper::GimpXToScreen(75);
	TRANSFORM(bouton[0])->position.Y = TRANSFORM(boutonContainer[0])->position.Y = PlacementHelper::GimpYToScreen(156);
	TEXT_RENDERING(bouton[1])->text = localizeAPI->text("mode_2", "Later");
	TRANSFORM(bouton[1])->position.X = PlacementHelper::GimpXToScreen(75);
	TRANSFORM(bouton[1])->position.Y = TRANSFORM(boutonContainer[1])->position.Y = PlacementHelper::GimpYToScreen(156+183);
	TEXT_RENDERING(bouton[2])->text = localizeAPI->text("mode_2", "No thanks");
	TRANSFORM(bouton[2])->position.X = PlacementHelper::GimpXToScreen(75);
	TRANSFORM(bouton[2])->position.Y = TRANSFORM(boutonContainer[2])->position.Y = PlacementHelper::GimpYToScreen(156+2*183);
}

void RateItStateManager::Enter() {
	LOGI("%s", __PRETTY_FUNCTION__);

	for (int i=0; i<3; i++) {
		RENDERING(boutonContainer[i])->hide = false;
		TEXT_RENDERING(bouton[i])->hide = false;
		BUTTON(boutonContainer[i])->enabled = true;
	}

	RENDERING(menubg)->hide = false;
	RENDERING(menufg)->hide = false;
	//~RENDERING(fond)->hide = false;
}

GameState RateItStateManager::Update(float dt) {
	if (BUTTON(boutonContainer[0])->clicked) {
		return ModeMenu;
	} else if(BUTTON(boutonContainer[1])->clicked){
		return ModeMenu;
	} else if(BUTTON(boutonContainer[2])->clicked){
		return ModeMenu;
	}
	return RateIt;
}

void RateItStateManager::Exit() {
	LOGI("%s", __PRETTY_FUNCTION__);

	for (int i=0; i<3; i++) {
		TEXT_RENDERING(bouton[i])->hide = true;
		RENDERING(boutonContainer[i])->hide = true;
		BUTTON(boutonContainer[i])->enabled = false;
	}

	RENDERING(menubg)->hide = true;
	RENDERING(menufg)->hide = true;
	//~RENDERING(fond)->hide = true;
}
