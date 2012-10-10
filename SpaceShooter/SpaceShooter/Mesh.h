/********************************************************************
    created:    8:10:2012   21:30
    filename:   Mesh.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Mesh_h__
#define Mesh_h__
#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/gl.h>
#include <vector>

class Mesh
{
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	std::vector<float> colors;
};

class MeshInfo
{
public:
	GLuint vertices;
	GLuint indices;
	GLuint numberOfIndices;
	GLuint normals;
};
#endif // Mesh_h__