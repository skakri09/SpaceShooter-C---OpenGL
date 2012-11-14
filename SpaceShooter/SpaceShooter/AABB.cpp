#include "AABB.h"


AABB::AABB()
{
}

AABB::~AABB()
{

}

void AABB::CreateAABB( std::vector<float>* vertices)
{
	m_Right = m_Left = m_Top = m_Bottom = m_Front = m_Back = 0;

#pragma region forloop
	for(unsigned int i = 0; i < vertices->size(); i+=3)
	{
		if(vertices->at(i) > m_Right)
		{
			m_Right = vertices->at(i);
		}
		else if(vertices->at(i) < m_Left)
		{
			m_Left = vertices->at(i);
		}

		if(vertices->at(i+1) > m_Top)
		{
			m_Top = vertices->at(i+1);
		}
		else if(vertices->at(i+1) < m_Bottom)
		{
			m_Bottom = vertices->at(i+1);
		}

		if(vertices->at(i+2) > m_Front)
		{
			m_Front = vertices->at(i+2);
		}
		else if(vertices->at(i+2) < m_Back)
		{
			m_Back = vertices->at(i+2);
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
}

void AABB::CreateAABB( Lib3dsVector* vertices, unsigned int size)
{
	m_Right = m_Left = m_Top = m_Bottom = m_Front = m_Back = 0;

#pragma region forloop
	for(unsigned int i = 0; i < size; i+=3)
	{
		if(vertices[i][0] > m_Right)
		{
			m_Right = vertices[i][0];
		}
		else if(vertices[i][0] < m_Left)
		{
			m_Left = vertices[i][0];
		}

		if(vertices[i][1] > m_Top)
		{
			m_Top = vertices[i][1];
		}
		else if(vertices[i][1] < m_Bottom)
		{
			m_Bottom = vertices[i][1];
		}

		if(vertices[i][2] > m_Front)
		{
			m_Front = vertices[i][2];
		}
		else if(vertices[i][2] < m_Back)
		{
			m_Back = vertices[i][2];
		}
	}
#pragma endregion

	m_Height = m_Top - m_Bottom;
	m_Width = m_Right - m_Left;
	m_Depth = m_Front - m_Back;

	m_LeftTopBack.setValues(m_Left, m_Top, m_Back);
	m_LeftTopFront.setValues(m_Left, m_Top, m_Front);
	m_RightTopFront.setValues(m_Right, m_Top, m_Front);
	m_LeftBottomBack.setValues(m_Left, m_Bottom, m_Back);
	m_RightBottomBack.setValues(m_Right, m_Bottom, m_Back);
	m_RightBottomFront.setValues(m_Right, m_Bottom, m_Front);
	m_RightTopBack.setValues(m_Right, m_Top, m_Back);
	m_LeftBottomFront.setValues(m_Left, m_Bottom, m_Front);

	orgMinPoint = minPoint = m_LeftBottomBack;
	orgMaxPoint = maxPoint = m_RightTopFront;
}

void AABB::SetPoints( Vector3D min, Vector3D max )
{
	minPoint = orgMinPoint = min;
	maxPoint = orgMaxPoint = max;
}
