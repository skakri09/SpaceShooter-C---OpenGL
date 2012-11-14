#include "Planet.h"


Planet::Planet(std::string planetName)
{
	rotation = 130.0f;
	CreatePlanet(planetName);
}

Planet::~Planet()
{
}

void Planet::Draw()
{
	glPushMatrix();
	glColor3f(0.0f, 0.5f, 0.0f);
	transformable.ApplyGLTransformations(true, true, false);
	glRotatef(rotation, 1.5f, 0.5f, 1.5f);
	vboDrawable.Draw();
	glColor3f(1, 1, 1);
	glPopMatrix();
}

void Planet::Update( GLfloat deltaTime )
{
	rotation += deltaTime*5.0f;
	if(rotation >= 360.0f)
	{
		rotation -= 360.0f;
	}
}

void Planet::InitPlanet( float xPos, float yPos, float zPos )
{
	transformable.Init(xPos, yPos, zPos, Vector3D::ZeroVec(), 0, 2.0f, Vector3D::ZeroVec());
}

void Planet::CreatePlanet( std::string meshName )
{
	if(!vboDrawable.HaveMeshInfo())
	{
		std::string meshPath = "..//3ds//Planets//";
		meshPath += meshName;
		std::shared_ptr<MeshInfo> meshInfo = MeshFactory::Inst()->GetMesh(meshPath);

		vboDrawable.SetMeshInfo(meshInfo);
	}
	InitPlanet(800, -400, -800);
}
