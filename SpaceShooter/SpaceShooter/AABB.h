/********************************************************************
	created:	9:10:2012   11:09
	filename: 	AABB.h
	author:		Kristian Skarseth
	
	purpose:	
*********************************************************************/
#ifndef AABB_h__
#define AABB_h__

#include "Vector3d.h"
#include <lib3ds/types.h>
#include <vector>

class AABB
{
public:
	AABB();
	~AABB();

protected:
	void CreateAABB(std::vector<float>* vertices);

	void CreateAABB( Lib3dsVector* vertices, unsigned int size);

	float m_Height;
	float m_Width;
	float m_Depth;

	float m_Left;
	float m_Right;
	float m_Top;
	float m_Bottom;
	float m_Back;
	float m_Front;

	Vector3D m_LeftTopBack;
	Vector3D m_RightTopBack;
	Vector3D m_LeftTopFront;
	Vector3D m_RightTopFront;
	Vector3D m_LeftBottomBack;
	Vector3D m_RightBottomBack;
	Vector3D m_LeftBottomFront;
	Vector3D m_RightBottomFront;

private:
	//Logger log;
};

#endif // AABB_h__
