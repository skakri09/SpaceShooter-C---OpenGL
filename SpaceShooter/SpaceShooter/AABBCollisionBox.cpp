#include "AABBCollisionBox.h"


AABBCollisionBox::AABBCollisionBox()
{
	drawAAB = true;
}

AABBCollisionBox::AABBCollisionBox(
	float minX, float maxX, float minY, float maxY,
	float minZ, float maxZ)
{
	orgMinPoint.setValues(minX, minY, minZ);
	minPoint = orgMinPoint;
	
	orgMaxPoint.setValues(maxX, maxY, maxZ);
	maxPoint = orgMaxPoint;
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
	
	for(unsigned int i = 0; i < SubBoxes.size(); i++)
	{
		SubBoxes.at(i)->Update(translationInfo);
	}
}

bool AABBCollisionBox::IsCollision( AABBCollisionBox* otherCollidable )
{
	Vector3D* oMin = otherCollidable->GetMin();
	Vector3D* oMax = otherCollidable->GetMax();

	if(maxPoint.getZ() < oMin->getZ()) return false;
	if(minPoint.getZ() > oMax->getZ()) return false;
	if(maxPoint.getX() < oMin->getX()) return false;
	if(maxPoint.getY() < oMin->getY()) return false;
	if(minPoint.getX() > oMax->getX()) return false;
	if(minPoint.getY() > oMax->getY()) return false;
	
	if(SubBoxes.empty())
	{
			return true;
	}
	else//If this collision box consist of more sub-boxes we loop trough them and check them
	{
		for(unsigned int i = 0; i < SubBoxes.size(); i++)
		{
			if(SubBoxes.at(i)->IsCollision(otherCollidable))
			{	
				return true;
			}
		}
		return false;
	}
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
	if(drawAAB)
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

		for(unsigned int i = 0; i < SubBoxes.size(); i++)
		{
			SubBoxes.at(i)->DrawAABB();
		}
	}
}

void AABBCollisionBox::SetDrawAAB( bool drawAAB, bool drawSubBoxes )
{
	this->drawAAB = drawAAB;
	for(unsigned int i = 0; i < SubBoxes.size(); i++)
	{
		SubBoxes.at(i)->SetDrawAAB(drawSubBoxes, true);
	}
}

void AABBCollisionBox::CreateSubBox( std::shared_ptr<AABBCollisionBox> newSubBox )
{
	SubBoxes.push_back(newSubBox);
}
