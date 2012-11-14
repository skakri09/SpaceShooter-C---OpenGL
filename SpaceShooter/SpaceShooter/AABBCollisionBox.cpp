#include "AABBCollisionBox.h"


AABBCollisionBox::AABBCollisionBox()

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
	
	minPoint = orgMinPoint;
	maxPoint = orgMaxPoint;

	minPoint *= translationInfo.scale;
	minPoint += translationInfo.position;
	
	maxPoint *= translationInfo.scale;
	maxPoint += translationInfo.position;
	

}

bool AABBCollisionBox::IsCollision( AABBCollisionBox* otherCollidable )
{
	Vector3D* oMin = otherCollidable->GetMin();
	Vector3D* oMax = otherCollidable->GetMax();

	if(maxPoint.getX() < oMin->getX()) return false;
	if(maxPoint.getY() < oMin->getY()) return false;
	if(maxPoint.getZ() < oMin->getZ()) return false;
	if(minPoint.getX() > oMax->getX()) return false;
	if(minPoint.getY() > oMax->getY()) return false;
	if(minPoint.getZ() > oMax->getZ()) return false;
	return true;
}

void AABBCollisionBox::CreateCollisionBox( std::vector<float>* vertices )
{
	AABB::CreateAABB(vertices);
}

void AABBCollisionBox::CreateCollisionBox( Lib3dsVector* vertices, unsigned int size )
{
	AABB::CreateAABB(vertices, size);
}

void AABBCollisionBox::DrawAABB()
{
	glPushMatrix();
	glBegin(GL_LINE_LOOP); 
	glVertex3f(maxPoint.getX(),maxPoint.getY(),minPoint.getZ()); 
	glVertex3f(minPoint.getX(),maxPoint.getY(),minPoint.getZ()); 
	glVertex3f(minPoint.getX(),minPoint.getY(),minPoint.getZ());
	glVertex3f(maxPoint.getX(),minPoint.getY(),minPoint.getZ()); 
	glEnd();

	glBegin(GL_LINE_LOOP); 
	glVertex3f(maxPoint.getX(),minPoint.getY(),maxPoint.getZ());
	glVertex3f(maxPoint.getX(),maxPoint.getY(),maxPoint.getZ());
	glVertex3f(minPoint.getX(),maxPoint.getY(),maxPoint.getZ());
	glVertex3f(minPoint.getX(),minPoint.getY(),maxPoint.getZ());
	glEnd();

	glBegin (GL_LINE_LOOP); 
	glVertex3f(maxPoint.getX(),maxPoint.getY(),minPoint.getZ()); 
	glVertex3f(maxPoint.getX(),maxPoint.getY(),maxPoint.getZ());
	glVertex3f(minPoint.getX(),maxPoint.getY(),maxPoint.getZ()); 
	glVertex3f(minPoint.getX(),maxPoint.getY(),minPoint.getZ()); 
	glEnd();

	glBegin (GL_LINE_LOOP);
	glVertex3f(maxPoint.getX(),minPoint.getY(),maxPoint.getZ());
	glVertex3f(minPoint.getX(),minPoint.getY(),maxPoint.getZ()); 
	glVertex3f(minPoint.getX(),minPoint.getY(),minPoint.getZ()); 
	glVertex3f(maxPoint.getX(),minPoint.getY(),minPoint.getZ()); 
	glEnd();
	glPopMatrix();
}
