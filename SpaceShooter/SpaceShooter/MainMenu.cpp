#include "MainMenu.h"


MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init(InputManager* input, GameState* gameState)
{
	skybox.initSkybox("skybox1", 100);
	this->input = input;
	selectedEntry = 0;

	playGameEntry = std::make_shared<PlayGameEntry>(gameState, 0.0f, 2.0f, 0.0f, 0.08f);
	quitGameEntry = std::make_shared<QuitGameEntry>(gameState, 0.0f, -5.0f, 0.0f, 0.08f);
	menuEntries.push_back(playGameEntry);
	menuEntries.push_back(quitGameEntry);
	
	menuEntries.at(selectedEntry)->SetIsSelected(true);
}

void MainMenu::UpdateMenu(float deltaTime)
{
	skybox.UpdateSkybox(deltaTime);
	HandleInput();
	for(unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries.at(i)->UpdateEntry(deltaTime);
	}
}

void MainMenu::DrawMenu()
{
	skybox.drawSkybox();

	for(unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries.at(i)->DrawEntry();
	}
}

void MainMenu::HandleInput()
{
	if(input->KeyDownOnce(SDLK_s))// && !input->KeyDownOnce(SDLK_w))
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
	}

	if(input->KeyDownOnce(SDLK_RETURN) || input->KeyDownOnce(SDLK_SPACE))
	{
		menuEntries.at(selectedEntry)->OnClicked();
	}
}

void MainMenu::OnEnteringMenu()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_MULTISAMPLE);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glShadeModel(GL_SMOOTH); 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	SetMenuLights();
	SetMenuFog();
}


void MainMenu::SetMenuLights()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	const static GLfloat ambient[] = 
	{ 0.898f, 0.694f, 0.227f, 0.0f };
	const static GLfloat diffuse[] = 
	{ 0.898f, 0.694f, 0.227f, 0.5f };
	const static GLfloat specular[] = 
	{ 0.898f, 0.694f, 0.227f, 0.0f };
	const static GLfloat position[] = 
	{ 0.0f, 0.0f, 500.0, 1.0f }; 

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

}

void MainMenu::SetMenuFog()
{
	glDisable(GL_FOG);
}

