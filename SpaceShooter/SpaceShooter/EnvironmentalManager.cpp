#include "EnvironmentalManager.h"


EnvironmentalManager::EnvironmentalManager()
{
}

EnvironmentalManager::~EnvironmentalManager()
{
}

void EnvironmentalManager::InitManager()
{
	MeshFactory::Inst()->LoadMesh("..//3ds//Planets//Endor//Endor.3ds");

	Environment.push_back(std::make_shared<Planet>("Endor//Endor.3ds"));
	Environment.push_back(std::make_shared<DeathStar>());
}

void EnvironmentalManager::Update( float deltaTime )
{
	for(unsigned int i = 0; i < Environment.size(); i++)
	{
		Environment.at(i)->Update(deltaTime);
	}
}

void EnvironmentalManager::DrawEnvironment()
{
	for(unsigned int i = 0; i < Environment.size(); i++)
	{
		Environment.at(i)->Draw();
	}
}

void EnvironmentalManager::ResetEnvironment()
{

}
