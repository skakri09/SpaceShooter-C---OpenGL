/********************************************************************
    created:    10:10:2012   14:19
    filename:   Mesh3dsLoader.h
    author:     Kristian Skarseth
    
    purpose:    The class can load .3ds files using lib3ds
*********************************************************************/
#ifndef Mesh3dsLoader_h__
#define Mesh3dsLoader_h__

#ifdef _WIN32
#include <windows.h>
#endif
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
#include "MeshInfo.h"
#include "Logger.h"
#include "BoundingSphere.h"

class Mesh3dsLoader
{
public:
    Mesh3dsLoader();
    ~Mesh3dsLoader();

	//Loads a .3ds file from the param path & filename
	//The function will take care of creating the VBOs
	//and loading them to the gpu. It returns a MeshInfo
	//object containing the IDs for the VBOs as well as
	//a collisionSphere object created from the loaded vertexes
	MeshInfo Load3dsMesh(std::string _3dsMeshFile);
	
private:
	Logger log;

	std::shared_ptr<BoundingSphere> collisionSphere;

	unsigned int GetNrOfFaces();

	unsigned int totalFaces;
	Lib3dsFile* model;

};

#endif // Mesh3dsLoader_h__