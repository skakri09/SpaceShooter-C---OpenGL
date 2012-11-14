/********************************************************************
    created:    26:10:2012   9:57
    filename:   VBODrawable.h
    author:     Kristian Skarseth
    
    purpose:    Gives functionality to draw with VBOs
*********************************************************************/
#ifndef VBODrawable_h__
#define VBODrawable_h__

#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/glew.h>

#include "MeshInfo.h"
#include "Logger.h"

class VBODrawable
{
public:
    VBODrawable();
    ~VBODrawable();
	
	//Draws the VBO held by the MeshInfo object
	//this class has. If it has not previously been
	//set we get an error and may crash.
	//The class handles choosing between drawing with 
	//arrays and elements based on the info in the MeshInfo obj.
	void Draw(bool enableClientStates = true);

	//Sets meshinfo for this object. 
	void SetMeshInfo(std::shared_ptr<MeshInfo> meshInfo);

	//Returns true if this class have received a MeshInfo object
	bool HaveMeshInfo();

	void EnableClientStates();

	void DisableClientStates();

private:
	Logger log;

	//MeshInfo meshInfo;
	std::shared_ptr<MeshInfo> meshInfo;

	bool haveMeshInfo;
};

#endif // VBODrawable_h__