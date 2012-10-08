#include "Collidable.h"


Collidable::Collidable() :log("Collidable", WARN)
{
}

Collidable::~Collidable()
{
}



bool Collidable::CheckForCollision( Collidable& otherCollidable )
{
	//if (RectA.X1 < RectB.X2 && RectA.X2 > RectB.X1 &&
	//	RectA.Y1 < RectB.Y2 && RectA.Y2 > RectB.Y1) 

	//	if not (B.x > A.x+A.dx or B.x+B.dx < A.x or
	//		B.y > A.y+A.dy or B.y+B.dy < A.y or
	//		B.z > A.z+A.dz or B.z+B.dz < A.z)
}


void Collidable::CreateCollisionBox(Mesh& mesh)
{
	m_Right = m_Left = m_Top = m_Bottom = m_Front = m_Back = mesh.vertices.at(0);

#pragma region forloop
	for(unsigned int i = 0; i < mesh.vertices.size(); i+=3)
	{
		if(mesh.vertices.at(i) > m_Right)
		{
			m_Right = mesh.vertices.at(i);
		}
		else if(mesh.vertices.at(i) < m_Left)
		{
			m_Left = mesh.vertices.at(i);
		}

		if(mesh.vertices.at(i+1) > m_Top)
		{
			m_Top = mesh.vertices.at(i+1);
		}
		else if(mesh.vertices.at(i+1) < m_Bottom)
		{
			m_Bottom = mesh.vertices.at(i+1);
		}

		if(mesh.vertices.at(i+2) > m_Front)
		{
			m_Front = mesh.vertices.at(i+2);
		}
		else if(mesh.vertices.at(i+2) < m_Back)
		{
			m_Back = mesh.vertices.at(i+2);
		}
	}
#pragma endregion

	m_Height = m_Top - m_Bottom;
	m_Width = m_Right - m_Left;
	m_Depth = m_Front - m_Back;

	log << INFO << "Created a collisionbox" << std::endl;
}


