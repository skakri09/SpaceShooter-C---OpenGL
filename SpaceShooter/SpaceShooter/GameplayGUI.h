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
#include "HPEntry.h"
#include "LivesEntry.h"
#include "ManagerInterface.h"
#include "ScoreTextEntry.h"
#include "ScoreValueEntry.h"
#include "ProjectileIcon.h"
#include "BossHP.h"

class GameplayGUI
{
public:
    GameplayGUI();
    ~GameplayGUI();

	void InitGUI(ManagerInterface* manager);

	void UpdateGUI(float deltaTime);

	void RenderGUI();


private:
	VBODrawable vbo;

	std::vector<std::shared_ptr<GUIEntry>> GuiEntries;

};

#endif // GameplayInformation_h__