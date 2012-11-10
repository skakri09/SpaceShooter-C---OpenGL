#include "GameManager.h"
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

GameManager::GameManager()
	: log("GameMan", WARN)
{
}

GameManager::~GameManager() {
}

void GameManager::init(InputManager* input) 
{
	this->input = input;
	TextFactory::Inst()->InitTextFactory();
	ProjectileManager::Inst()->InitProjectileManager();
	SpaceShipManager::Inst()->InitManager(input);
	ParticleManager::Inst()->InitParticleManager();
	environment.InitManager();
	skybox.initSkybox("skybox1", 100);
}

void GameManager::RenderGame() 
{
	glPushMatrix();

	skybox.drawSkybox();

	environment.DrawEnvironment();
	ParticleManager::Inst()->DrawParticles();
	SpaceShipManager::Inst()->DrawSpaceShips();
	ProjectileManager::Inst()->DrawProjectiles();

	glPopMatrix();
}

void GameManager::UpdateGame(float deltaTime)
{
	environment.Update(deltaTime);
	skybox.UpdateSkybox(deltaTime);
	ParticleManager::Inst()->UpdateParticles(deltaTime);
	SpaceShipManager::Inst()->UpdateManager(deltaTime);
	ProjectileManager::Inst()->UpdateProjectiles(deltaTime);
}

void GameManager::OnEnteringGameState()
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

void GameManager::SetGameLights()
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

void GameManager::SetGameFog()
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
