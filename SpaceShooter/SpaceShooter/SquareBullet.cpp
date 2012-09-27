#include "SquareBullet.h"

CSquareBullet::CSquareBullet() :CProjectile(5.0f)
{
	CreateDrawable();
}

CSquareBullet::~CSquareBullet()
{

}

void CSquareBullet::CreateDrawable()
{
	displayList = CProjectileFactory::Inst()->getDisplayList(SIMPLE_BULLET);

	if(displayList == -1)
	{
		displayList = glGenLists(1);
		CProjectileFactory::Inst()->addDisplayList(SIMPLE_BULLET, CDrawable::displayList);
		glNewList(displayList, GL_COMPILE);
		glBegin(GL_QUADS);
		
		//front square
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 1.0f, 0.0f);

		//right square
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, -3.0f);
		glVertex3f(0.5f, 1.0f, -3.0f);
		glVertex3f(0.5f, 1.0f, 0.0f);

		//back square
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.5f, 0.0f, -3.0f);
		glVertex3f(-0.5f, 0.0f, -3.0f);
		glVertex3f(-0.5f, 1.0f, -3.0f);
		glVertex3f(0.5f, 1.0f, -3.0f);

		//left square
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, -3.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 1.0f, -3.0f);

		//top square
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-0.5f, 1.0f, 0.0f);
		glVertex3f(0.5f, 1.0f, 0.0f);
		glVertex3f(0.5f, 1.0f, -3.0f);
		glVertex3f(-0.5f, 1.0f, -3.0f);

		//bottom square
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, -3.0f);
		glVertex3f(0.5f, 0.0f, -3.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);

		glEnd();
		glEndList();
	}	
}


