/********************************************************************
    created:    10:11:2012   14:58
    filename:   GameplayInformation.h
    author:     Kristian Skarseth
    
    purpose:    Display and handle all GUI information on the screen
*********************************************************************/
#ifndef GameplayInformation_h__
#define GameplayInformation_h__

#include <gl/glew.h>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

#include "TextFactory.h"
#include "GameConstants.h"
#include "SpaceShipManager.h"
#include "VBODrawable.h"
#include "Transformable.h"
#include "GUIEntry.h"

class GameplayInformation
{
public:
    GameplayInformation();
    ~GameplayInformation();

	void InitGameplayInformation();

	void UpdateGameplayInformation(float deltaTime);

	void RenderGameplayInformation();


private:
	VBODrawable vbo;

	std::vector<std::shared_ptr<GUIEntry>> GuiEntries;

	Transformable playerHPPos;
	std::shared_ptr<VboString> PlayerHP;
	std::string playerHPString;
	void RenderPlayerHP();

};

#endif // GameplayInformation_h__