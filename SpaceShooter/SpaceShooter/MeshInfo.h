/********************************************************************
    created:    10:10:2012   22:55
    filename:   MeshInfo.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef MeshInfo_h__
#define MeshInfo_h__


class MeshInfo
{
public:
	GLuint vertices;
	GLuint indices;
	GLuint numberOfIndices;
	GLuint normals;
	GLuint textCoords;
	//std::shared_ptr<BoundingSphere> collisionSphere;
};

#endif // MeshInfo_h__