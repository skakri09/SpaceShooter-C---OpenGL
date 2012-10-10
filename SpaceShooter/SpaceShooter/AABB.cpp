#include "AABB.h"


AABB::AABB()
	:log("AABB", WARN)
{
}

AABB::~AABB()
{

}

void AABB::CreateAABB( Mesh& mesh )
{
	m_Right = m_Left = m_Top = m_Bottom = m_Front = m_Back = 0;

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

	m_LeftTopBack.setValues(m_Left, m_Top, m_Back);
	m_RightTopBack.setValues(m_Right, m_Top, m_Back);
	m_LeftTopFront.setValues(m_Left, m_Top, m_Front);
	m_RightTopFront.setValues(m_Right, m_Top, m_Front);
	m_LeftBottomBack.setValues(m_Left, m_Bottom, m_Back);
	m_RightBottomBack.setValues(m_Right, m_Bottom, m_Back);
	m_LeftBottomFront.setValues(m_Left, m_Bottom, m_Front);
	m_RightBottomFront.setValues(m_Right, m_Bottom, m_Front);

	log << INFO << "Created a AxisAlignedBoundingBox collisionbox" << std::endl;
}
