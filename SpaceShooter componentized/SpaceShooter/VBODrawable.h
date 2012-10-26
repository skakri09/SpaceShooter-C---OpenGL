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
#include <gl/gl.h>

#include "MeshInfo.h"
#include "Logger.h"
class VBODrawable
{
public:
    VBODrawable();
    ~VBODrawable();

	//Draws the VBO associated with this class'
	//MeshInfo object trough arrays.
	void DrawWithArrays();

	//Draws the VBO associated with this class'
	//MeshInfo object with indices. If the MeshInfo
	//objects indices array is not in use or otherwise
	//faulty, the drawing will be wrong.
	void DrawWithIndices();

	void SetMeshInfo(MeshInfo meshInfo);

	//Returns true if this class have recieved a MeshInfo object
	bool HaveMeshInfo();

private:
	Logger log;

	MeshInfo meshInfo;

	//Enables glClientStates based on the parameters
	void EnableClientStates(bool colorArray = false,
							bool normalArray = true,
							bool vertexArray = true,
							bool elementArray = false);
	
	//Disables all glClientStates currently enabled
	void DisableClientStates();

	//Bools for currently enabled glClientStates
	bool colorArrayEnabled;
	bool normalArrayEnabled;
	bool vertexArrayEnabled;
	bool elementArrayEnabled;
	
	bool haveMeshInfo;
};

#endif // VBODrawable_h__