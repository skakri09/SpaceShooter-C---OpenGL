#include "MainMenu.h"


MainMenu::MainMenu()
	:log("mainMenu", WARN)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init(InputManager* input, GameState* gameState)
{
	cam.SetCameraPosition(0, 0, 35);
	cam.SetSkybox("skybox1");
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
	this->deltaTime = deltaTime;
	cam.Control(20*deltaTime, 30*deltaTime, input);
	HandleInput();
	UpdateSelectionShip(deltaTime);
	for(unsigned int i = 0; i < menuEntries.size(); i++)
	{
		menuEntries.at(i)->UpdateEntry(deltaTime);
	}
}

void MainMenu::DrawMenu()
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
	if(!menuShip)
	{
		menuShip = std::make_shared<PlayerSpaceShip>();
	}
	Vector3D* pos = menuEntries.at(selectedEntry)->GetPosition();
	menuShip->InitSpaceShip(pos->getX(), pos->getY(), pos->getZ(), 270, 0, 1, 0, 0, 0, 0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

}

void MainMenu::SetMenuFog()
{
	glDisable(GL_FOG);
}

void MainMenu::UpdateSelectionShip(float deltaTime)
{

	menuShip->Update(deltaTime);
	menuShip->transformable.SetPos(*menuEntries.at(selectedEntry)->GetPosition());
	menuShip->transformable.SetXPos(menuShip->transformable.getXPos() - 3);

}

