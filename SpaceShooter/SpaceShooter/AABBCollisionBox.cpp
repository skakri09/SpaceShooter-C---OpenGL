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
	height = m_Height*biggest;
	width = m_Width*biggest;
	depth = m_Depth*biggest;

	minPoint *= translationInfo.scale;
	minPoint.setZ(minPoint.getZ()-depth);
	minPoint += translationInfo.position;
	
	maxPoint *= translationInfo.scale;
	maxPoint.setZ(maxPoint.getZ()-depth);
	maxPoint += translationInfo.position;
	

	//minPoint = (orgMinPoint + translationInfo.position)+(orgMinPoint * translationInfo.scale);
	////minPoint = (orgMinPoint * translationInfo.scale);

	//maxPoint = (orgMaxPoint + translationInfo.position)+(orgMaxPoint * translationInfo.scale);
	////maxPoint = (orgMaxPoint * translationInfo.scale);
}

bool AABBCollisionBox::IsCollision( AABBCollisionBox* otherCollidable )
{
	Vector3D* oMin = otherCollidable->GetMin();
	Vector3D* oMax = otherCollidable->GetMax();

	if (minPoint.getX() + width						< oMin->getX())		return false;
	if (minPoint.getY() + height					< oMin->getY())		return false;
	if (minPoint.getZ()	+ depth						< oMin->getZ())		return false;
	if (oMin->getX()	+ otherCollidable->width	< minPoint.getX())	return false;
	if (oMin->getY()	+ otherCollidable->height	< minPoint.getY())	return false;
	if (oMin->getZ()	+ otherCollidable->depth	< minPoint.getZ())	return false;

	return true;

	return
		minPoint.getX() > oMax->getX() || maxPoint.getX() < oMin->getX() ||
		minPoint.getY() >oMax->getY() || maxPoint.getY() <oMin->getY() ||
		minPoint.getZ() > oMax->getZ() || maxPoint.getZ() < oMin->getZ();


	if( maxPoint.getX() < oMin->getX() || minPoint.getX() > oMax->getX() )
		return false;
	if( maxPoint.getY() < oMin->getY() || minPoint.getY() > oMax->getY() )
		return false;
	if( maxPoint.getZ() < oMin->getZ() || minPoint.getZ() > oMax->getZ() )
		return false;

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
