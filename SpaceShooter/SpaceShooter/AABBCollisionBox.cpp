#include "AABBCollisionBox.h"


AABBCollisionBox::AABBCollisionBox() 
	:log("AABBCollisionBox", WARN)

{
}

AABBCollisionBox::~AABBCollisionBox()
{
}

void AABBCollisionBox::Update( CollisionTransformationInfo& translationInfo )
{
	float biggest = translationInfo.scale.getX();
	if(biggest < translationInfo.scale.getY()){biggest = translationInfo.scale.getY();}
	if(biggest < translationInfo.scale.getZ()){biggest = translationInfo.scale.getZ();}

	AABB::UpdateAABBWorldPosition(&translationInfo.position);
	//CollisionMidpoint = (LocalMidpoint*biggest) + translationInfo.position;
	//CollisionRadius = LocalRadius * biggest;
}

Vector3D AABBCollisionBox::IsCollision( AABBCollisionBox* otherCollidable )
{
	return false;

}

void AABBCollisionBox::CreateCollisionBox( std::vector<float>* vertices )
{
	AABB::CreateAABB(vertices);
}

void AABBCollisionBox::CreateCollisionBox( Lib3dsVector* vertices, unsigned int size )
{
	AABB::CreateAABB(vertices, size);
}
