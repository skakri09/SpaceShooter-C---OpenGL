/********************************************************************
    created:    10:10:2012   14:19
    filename:   Mesh3dsLoader.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Mesh3dsLoader_h__
#define Mesh3dsLoader_h__

#ifdef _WIN32
#include <windows.h>
#endif
//#include <SDL.h>
#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <IL/il.h>
#include <IL/ilu.h>
#include <vector>
#include <memory>
#include "Image.h"
#include "Mesh.h"
#include "Logger.h"
#include "BoundingSphere.h"

class Mesh3dsLoader
{
public:
    Mesh3dsLoader();
    ~Mesh3dsLoader();

	MeshInfo Load3dsMesh(std::string _3dsMeshFile);
	
	//Returning the collisionSphere by value as we wish to transfer complete
	//ownership anyway and store it in a none-pointer fashion
	std::shared_ptr<BoundingSphere> GetBoundingSphere(){return collisionSphere;}
	

	

private:
	Logger log;

	std::shared_ptr<BoundingSphere> collisionSphere;

	unsigned int GetNrOfFaces();

	unsigned int totalFaces;
	Lib3dsFile* model;
	
	MeshInfo meshInfo;
	
};

#endif // Mesh3dsLoader_h__