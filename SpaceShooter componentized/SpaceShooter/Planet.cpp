#include "Planet.h"


Planet::Planet(std::string meshName)
{
	this->meshName = meshName;
}

Planet::~Planet()
{
}

void Planet::Draw()
{
	glPushMatrix();

	ApplyTransformations();

	//DrawWithArrays();

	glPopMatrix();
}

void Planet::Update( GLfloat deltaTime )
{

}

void Planet::CreateGameObject()
{
	meshInfo = MeshFactory::Inst()->GetMesh(meshName);
	collisionSphere = *meshInfo.collisionSphere;
}
