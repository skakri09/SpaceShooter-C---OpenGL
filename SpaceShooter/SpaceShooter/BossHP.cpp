#include "BossHP.h"


BossHP::BossHP()
{
}

BossHP::~BossHP()
{
}

void BossHP::Init()
{
	_vbo.SetMeshInfo(MeshFactory::Inst()->GetMesh("..//xml//hpBar.xml"));
	bossMaxHP = static_cast<float>(SpaceShipManager::Inst()->GetStarDestroyer()->GetSpaceshipMaxHP());
	transformable.Init(1.2f, 3.6f, -5, Vector3D::ZeroVec(), 1.0f, Vector3D::ZeroVec());
}

void BossHP::Update( float deltaTime )
{
	bossHP = static_cast<float>(SpaceShipManager::Inst()->GetStarDestroyer()->GetSpaceshipHP());
	
	xScale = bossHP/bossMaxHP;
}

void BossHP::Draw( VBODrawable* vbo )
{
	glPushMatrix();
	glColor4f(0, 0.3f, 0, 1);
	GUIEntry::transformable.ApplyGLTransformations(true, true, false);
	glScalef(5.0f, 0.3f, 1.0f);
	glScalef(xScale, 1, 1);
	_vbo.Draw();

	glColor4f(1, 1, 1, 1);
	glPopMatrix();
}
