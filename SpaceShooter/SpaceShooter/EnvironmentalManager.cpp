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
	planet.CreatePlanet("Endor//Endor.3ds");
}

void EnvironmentalManager::Update( float deltaTime )
{
	planet.Update(deltaTime);
}

void EnvironmentalManager::DrawEnvironment()
{
	planet.Draw();
}
