#include "DeathStar.h"


DeathStar::DeathStar()
{
	rotation = 0.0f;
	InitDeathstar(-750, 200, -800);
}

DeathStar::~DeathStar()
{
}

void DeathStar::Draw()
{
	glPushMatrix();
	transformable.ApplyGLTransformations(true, true, false);
	glRotatef(rotation, 0.2f, 1.0f, 0.0f);

	texturable.BindTexture("DSP");
	vboDrawable.Draw();

	texturable.UnbindTexture();
	glPopMatrix();
}

void DeathStar::Update( GLfloat deltaTime )
{
	rotation += deltaTime*5.0f;
	if(rotation >= 360.0f)
	{
		rotation -= 360.0f;
	}
}

void DeathStar::LoadDeathstar()
{
	if(!vboDrawable.HaveMeshInfo())
	{
		std::shared_ptr<MeshInfo> meshInfo = MeshFactory::Inst()->GetMesh("..//3ds//DeathStar//DeathStar.3ds");
		vboDrawable.SetMeshInfo(meshInfo);
	}
	texturable.InitTexture("..//3ds//DeathStar//DeathStarPanels.jpg", "DSP");
}

void DeathStar::InitDeathstar( float xPos, float yPos, float zPos )
{
	LoadDeathstar();
	transformable.Init(xPos, yPos, zPos, Vector3D::ZeroVec(), 0, 2.0f, Vector3D::ZeroVec());
}
