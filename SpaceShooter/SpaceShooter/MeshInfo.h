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
	MeshInfo()
	{	
		haveVertices = false; 
		haveIndices = false;
		haveNormals = false; 
		haveTexCoords = false;
		haveColors = false;
	}

	GLuint vertices;	bool haveVertices;
	GLuint indices;		bool haveIndices;
	GLuint numberOfIndices;
	GLuint normals;		bool haveNormals;
	GLuint textCoords;	bool haveTexCoords;
	GLuint colors;		bool haveColors;
	GLenum mode;

	std::shared_ptr<BoundingSphere> collisionSphere;
};

#endif // MeshInfo_h__