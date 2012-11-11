#include "Menu.h"


Menu::Menu(std::string skyboxName)
{
	this->skyboxName = skyboxName;
}

Menu::~Menu()
{
}

void Menu::Init( InputManager* input, GameState* gameState )
{
	cam.SetCameraPosition(0, 0, 35);
	cam.SetSkybox(skyboxName);
	this->input = input;
	this->gameState = gameState;
	for(unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries.at(i)->SetIsSelected(false);
	}
	selectedEntry = 0;
}

void Menu::UpdateMenu( float deltaTime )
{
	this->deltaTime = deltaTime;
	HandleInput();
	UpdateSelectionShip(deltaTime);
	for(unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries.at(i)->UpdateEntry(deltaTime);
	}
}

void Menu::RenderMenu()
{
	glPushMatrix();
	cam.RenderCamera();

	menuShip->Draw();
	for(unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries.at(i)->DrawEntry();
	}

	glPopMatrix();
}

void Menu::OnEnteringMenu()
{
	if(!menuShip)
	{
		menuShip = std::make_shared<PlayerSpaceShip>();
	}
	Vector3D* pos = menuEntries.at(selectedEntry)->GetPosition();
	menuShip->InitSpaceShip(pos->getX(), pos->getY(), pos->getZ(), 270, 0, 1, 0, 0, 0, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	const static GLfloat ambient[] = 
	{ 0.2f, 0.2f, 0.2f, 0.1f, 0.1f };
	const static GLfloat diffuse[] = 
	{ 0.2f, 0.2f, 0.2f, 0.1f };
	const static GLfloat specular[] = 
	{ 0.898f, 0.694f, 0.227f, 0.0f };
	const static GLfloat position[] = 
	{ 0.0f, 0.0f, 50.0, 1.0f }; 

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glDisable(GL_FOG);
}

void Menu::UpdateSelectionShip( float deltaTime )
{
	menuShip->Update(deltaTime);
	menuShip->transformable.SetPos(*menuEntries.at(selectedEntry)->GetPosition());
	menuShip->transformable.SetXPos(menuShip->transformable.getXPos() - 3);
}

void Menu::HandleInput()
{
	if(input->KeyDownOnce(SDLK_s))
	{
		if(selectedEntry >= menuEntries.size()-1)
		{
			menuEntries.at(selectedEntry)->SetIsSelected(false);
			selectedEntry = 0;
			menuEntries.at(selectedEntry)->SetIsSelected(true);
		}
		else
		{
			menuEntries.at(selectedEntry)->SetIsSelected(false);
			++selectedEntry;
			menuEntries.at(selectedEntry)->SetIsSelected(true);
		}
		SoundManager::Inst()->PlayEffect("button");
	}
	else if(input->KeyDownOnce(SDLK_w) && !input->KeyDownOnce(SDLK_s))
	{
		if(selectedEntry <= 0)
		{
			menuEntries.at(selectedEntry)->SetIsSelected(false);
			selectedEntry = menuEntries.size()-1;
			menuEntries.at(selectedEntry)->SetIsSelected(true);
		}
		else
		{
			menuEntries.at(selectedEntry)->SetIsSelected(false);
			--selectedEntry;
			menuEntries.at(selectedEntry)->SetIsSelected(true);
		}
		SoundManager::Inst()->PlayEffect("button");
	}

	if(input->KeyDownOnce(SDLK_RETURN) || input->KeyDownOnce(SDLK_SPACE))
	{
		menuEntries.at(selectedEntry)->OnClicked();
	}
}


