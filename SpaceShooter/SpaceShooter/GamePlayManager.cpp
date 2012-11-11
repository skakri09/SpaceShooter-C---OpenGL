#include "GamePlayManager.h"
#include "GLUtils/GLUtils.hpp"

#include <Windows.h>
#include <GL/GL.h>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <assert.h>
#include <stdexcept>

using std::cerr;
using std::endl;
using GLUtils::checkGLErrors;

GamePlayManager::GamePlayManager()
	: log("GameMan", WARN)
{
}

GamePlayManager::~GamePlayManager() {
}

void GamePlayManager::InitGamePlayManager(InputManager* input, GameState* gameState) 
{
	this->input = input;
	TextFactory::Inst()->InitTextFactory();
	ProjectileManager::Inst()->InitProjectileManager();
	SpaceShipManager::Inst()->InitManager(input, gameState, &score);
	ParticleManager::Inst()->InitParticleManager();
	environment.InitManager();

	cam.SetCameraPosition(0, 0, CAMERA_POS);
	cam.SetSkybox("skybox1");

	gpi.InitGUI(&score);
}

void GamePlayManager::RenderGame() 
{
	glPushMatrix();
	
	cam.RenderCamera();
	
	environment.DrawEnvironment();
	ParticleManager::Inst()->DrawParticles();
	SpaceShipManager::Inst()->DrawSpaceShips();
	ProjectileManager::Inst()->DrawProjectiles();

	gpi.RenderGUI();

	glPopMatrix();
}

void GamePlayManager::Update(float deltaTime)
{
	environment.Update(deltaTime);

	cam.Control(15.0f*deltaTime, 40.0f*deltaTime, input);
	/*Vector3D cameraPos(*SpaceShipManager::Inst()->GetPlayer()->transformable.getPosition());
	cameraPos.setZ(cameraPos.getZ() + 10);
	cameraPos.setY(cameraPos.getY() + 3);
	cam.SetCameraPosition(&cameraPos);*/
	ParticleManager::Inst()->Update(deltaTime);
	SpaceShipManager::Inst()->Update(deltaTime);
	ProjectileManager::Inst()->Update(deltaTime);
	score.Update(deltaTime);
	gpi.UpdateGUI(deltaTime);
}

void GamePlayManager::OnEnteringGameState()
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

	SetGameLights();
	SetGameFog();
}

void GamePlayManager::SetGameLights()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	const static GLfloat ambient[] = 
	{ 0.0f, 0.0f, 0.0f, 1.0f };
	const static GLfloat diffuse[] = 
	{ 1.0f, 1.0f, 1.0f, 0.5f };
	const static GLfloat specular[] = 
	{ 0.0f, 1.0f, 0.0f, 1.0f };
	const static GLfloat position[] = 
	{ 0.0f, 0.0f, -500.0, 1.0f }; 
	const static GLfloat position2[] = 
	{ -500.0f, -500.0f, 0.0, 0.0f }; 

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightfv(GL_LIGHT1, GL_POSITION, position2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);      
}

void GamePlayManager::SetGameFog()
{
	GLfloat fogColor[4]= {0.0f, 0.0f, 0.0f, 1.0f}; 
	//GL_EXP, GL_EXP2, GL_LINEAR
	glFogi(GL_FOG_MODE, GL_LINEAR);       
	glFogfv(GL_FOG_COLOR, fogColor);           
	glFogf(GL_FOG_DENSITY, 0.45f);          
	glHint(GL_FOG_HINT, GL_NICEST);      
	glFogf(GL_FOG_START, 300.0f);         
	glFogf(GL_FOG_END, FRUSTUM_DEPTH);              
	glEnable(GL_FOG);   
}
