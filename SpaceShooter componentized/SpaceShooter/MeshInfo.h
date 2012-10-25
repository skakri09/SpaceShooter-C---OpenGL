/********************************************************************
    created:    12:10:2012   15:15
    filename:   MeshInfo.h
    author:     Kristian Skarseth
    
    purpose:	The meshinfo class holds information about a mesh that
				has been uploaded to the gpu. 
*********************************************************************/
#ifndef MeshInfo_h__
#define MeshInfo_h__


#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>
#include "BoundingSphere.h"
#include <memory>

class BoundingSphere;
class MeshInfo
{
public:
	GLuint vertices;
	GLuint indices;
	GLuint numberOfIndices;
	GLuint normals;
	GLuint textCoords;
	std::shared_ptr<BoundingSphere> collisionSphere;
};

#endif // MeshInfo_h__