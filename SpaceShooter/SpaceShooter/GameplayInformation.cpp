#include "GameplayInformation.h"


GameplayInformation::GameplayInformation()
{
}

GameplayInformation::~GameplayInformation()
{
}

void GameplayInformation::InitGameplayInformation()
{
	int hp = SpaceShipManager::Inst()->GetPlayer()->GetSpaceshipHP();
	unsigned int lives = SpaceShipManager::Inst()->GetPlayer()->GetLives();
	std::stringstream hplives;
	hplives << "lives: " << lives << " hp: " << hp;
	playerHPString = hplives.str();
	PlayerHP = TextFactory::Inst()->GetVboString(&playerHPString);
	playerHPPos.Init(-10, 0, 0, Vector3D::ZeroVec(), 0, 0.05f, Vector3D::ZeroVec());
}

void GameplayInformation::UpdateGameplayInformation(float deltaTime)
{
	for(unsigned int i = 0; i < GuiEntries.size(); i++)
	{
		GuiEntries.at(i)->Update(deltaTime);
	}
	int hp = SpaceShipManager::Inst()->GetPlayer()->GetSpaceshipHP();
	unsigned int lives = SpaceShipManager::Inst()->GetPlayer()->GetLives();
	std::stringstream hplives;
	hplives << "lives: " << lives << " hp: " << hp;
	std::string hpstring = hplives.str();
	if(hpstring != playerHPString)
	{
		playerHPString = hpstring;
		PlayerHP = TextFactory::Inst()->GetVboString(&playerHPString);
	}
	
}

void GameplayInformation::RenderGameplayInformation()
{
	for(unsigned int i = 0; i < GuiEntries.size(); i++)
	{
		GuiEntries.at(i)->Draw(&vbo);
	}

	RenderPlayerHP();
}

void GameplayInformation::RenderPlayerHP()
{
	glPushMatrix();
	playerHPPos.ApplyGLTransformations(true, true, false);
	for(unsigned int i = 0; i < PlayerHP->vboLetters.size(); i++)
	{
		glPushMatrix();

		PlayerHP->vboLetters.at(i).stringPosition.ApplyGLTransformations(true, true, false);
		vbo.SetMeshInfo(PlayerHP->vboLetters.at(i).meshInfo);
		vbo.Draw();

		glPopMatrix();
	}
	glPopMatrix();
}
