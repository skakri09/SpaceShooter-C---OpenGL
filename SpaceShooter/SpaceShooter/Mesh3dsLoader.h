/********************************************************************
    created:    10:10:2012   14:19
    filename:   Mesh3dsLoader.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef Mesh3dsLoader_h__
#define Mesh3dsLoader_h__

#include <Windows.h>
#include <SDL.h>
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

class Mesh3dsLoader
{
public:
    Mesh3dsLoader();
    ~Mesh3dsLoader();

	MeshInfo Load3dsMesh(std::string _3dsMeshFile);

	//MeshInfo& GetMeshInfo();

private:
	Logger log;

	unsigned int GetNrOfFaces();

	unsigned int totalFaces;
	Lib3dsFile* model;
	
	MeshInfo meshInfo;

};

#endif // Mesh3dsLoader_h__