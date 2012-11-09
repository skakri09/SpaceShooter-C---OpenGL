/********************************************************************
    created:    11:10:2012   17:51
    filename:   MeshFactory.h
    author:     Kristian Skarseth
    
    purpose:    A factory for getting meshes. The factory will take care
				of loading meshes that has not allready been loaded.
*********************************************************************/
#ifndef MeshFactory_h__
#define MeshFactory_h__

#include <map>
#include <memory>

#include "Mesh3dsLoader.h"
#include "MeshXmlLoader.h"
#include "Logger.h"

class MeshFactory
{
public:
	//The public access function for the mesh factory
   static MeshFactory* Inst();

	//Returns a meshInfo object containing info for the 
	//requested mesh object if it exists. If it has not been 
	//loaded yet, that is done automatically
	std::shared_ptr<MeshInfo> GetMesh(std::string meshName);

	//Loads a mesh to the GPU if it has not allready been loaded
	//This should be done when loading a new game/level to all 
	//meshes we want to use, so we dont have to do it during gameplay
	//as it's a rather slow process and will cause a small freeze
	void LoadMesh(std::string meshName);


private:
	//hidden c/dtor as it's a singleton
	MeshFactory();
	~MeshFactory();
	Logger log;

	//Helper function for Load/getMesh functions. Returns the last n chars
	//after the '.' in a filepath, aka the file extension
	std::string GetExtension(std::string& filePath);

	std::map<std::string, std::shared_ptr<MeshInfo>> LoadedMeshes;

	Mesh3dsLoader mesh3dsLoader;
	MeshXmlLoader xmlMeshLoader;
};

#endif // MeshFactory_h__