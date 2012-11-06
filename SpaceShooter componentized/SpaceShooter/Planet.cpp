#include "Planet.h"


Planet::Planet(/*std::string meshName*/)
{
	//this->meshName = meshName;
	//CreateGameObject();
	rotation = 0.0f;
}

Planet::~Planet()
{
}

void Planet::Draw()
{
	glPushMatrix();

	transformable.ApplyGLTransformations(true, true, false);
	glRotatef(rotation, 1.5f, 0.5f, 1.5f);
	vboDrawable.Draw();

	glPopMatrix();
}

void Planet::Update( GLfloat deltaTime )
{
	rotation += deltaTime*20.0f;
	if(rotation >= 360.0f)
	{
		rotation -= 360.0f;
	}
}

void Planet::CreateGameObject()
{
	/*if(!vboDrawable.HaveMeshInfo())
	{
		std::string meshPath = "..//3ds//Planets//";
		meshPath += meshName;
		MeshInfo meshInfo = MeshFactory::Inst()->GetMesh(meshPath);

		vboDrawable.SetMeshInfo(meshInfo);
		collisionSphere = *meshInfo.collisionSphere;
	}*/
	
}

void Planet::InitPlanet( float xPos, float yPos, float zPos )
{
	Vector3D zeroVec;
	transformable.Init(xPos, yPos, zPos, zeroVec, 0, 0.5f, zeroVec);
}

void Planet::CreatePlanet( std::string meshName )
{
	if(!vboDrawable.HaveMeshInfo())
	{
		std::string meshPath = "..//3ds//Planets//";
		meshPath += meshName;
		MeshInfo meshInfo = MeshFactory::Inst()->GetMesh(meshPath);

		vboDrawable.SetMeshInfo(meshInfo);
		//collisionSphere = *meshInfo.collisionSphere;
	}
	InitPlanet(300, 100, -500);
}
