#include "WeaponUpgrade.h"

WeaponUpgrade::WeaponUpgrade(ProjectileTypes thisType, 
	Vector3D* startPos, 
	Vector3D targetPos,
	float velocity,
	float scale)
{
	this->targetPos = targetPos;
	Vector3D vel = targetPos - *startPos;
	vel.Normalize();
	vel*= velocity;

	transformable.Init(*startPos, scale, vel);
	rotation = 0.0f;

	this->thisType = thisType;
	CreateBox(thisType);

	Vector3D minV(-0.5f, -0.5f, -0.5f);
	Vector3D maxV(0.5f, 0.5f, 0.5f);

	aabb.SetPoints(minV, maxV);
}

WeaponUpgrade::~WeaponUpgrade()
{

}

void WeaponUpgrade::Update( float deltaTime )
{
	aabb.Update(transformable.GetCollisionTransformationInfo());
	transformable.Update(deltaTime);
	if(transformable.getZPos() >= targetPos.getZ())
	{
		FlagForKill();
	}
	rotation+=deltaTime*100;
	if(rotation >= 360.0f)
	{
		rotation-= 360.0f;
	}
}

void WeaponUpgrade::Draw()
{
	glPushMatrix();

	
	transformable.ApplyGLTransformations(true, true, false);
	texturable.BindTexture(textureName);
	vbo.EnableClientStates();
	glRotatef(rotation, 1, 1, 1);
	vbo.Draw(false);
	glRotatef(90, 1, 0, 0);
	vbo.Draw(false);
	glRotatef(90, 1, 0, 0);
	vbo.Draw(false);
	glRotatef(90, 1, 0, 0);
	vbo.Draw(false);
	glRotatef(90, 0, 1, 0);
	vbo.Draw(false);
	glRotatef(180, 0, 1, 0);
	vbo.Draw(false);

	vbo.DisableClientStates();
	texturable.UnbindTexture();

	glPopMatrix();
}

void WeaponUpgrade::CreateBox( ProjectileTypes projectileType )
{	
	switch(projectileType)
	{
	case DOUBLE_LASER:
		textureName = "DoubleLaser.png";
		break;
	case TRIPLE_CONE_LASER:
		textureName = "TripleLaser.png";
		break;
	case QUAD_LASER:
		textureName = "QuadLaser.png";
		break;
	case DOUBLE_TRIPLE_CONE_LASER:
		textureName = "DoubleTripleLaser.png";
		break;
	}
	std::string texturePath = "..//images//" + textureName;
	texturable.InitTexture(texturePath, textureName);
	vbo.SetMeshInfo(MeshFactory::Inst()->GetMesh("..//xml//boxableSquare.xml"));
}
