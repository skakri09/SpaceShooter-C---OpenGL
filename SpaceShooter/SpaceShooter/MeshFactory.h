/********************************************************************
    created:    11:10:2012   17:51
    filename:   MeshFactory.h
    author:     Kristian Skarseth
    
    purpose:    A factory for 
*********************************************************************/
#ifndef MeshFactory_h__
#define MeshFactory_h__

#include <map>

#include "Mesh3dsLoader.h"
#include "MeshXmlLoader.h"

class MeshFactory
{
public:
   static MeshFactory* Inst();

	MeshInfo GetMesh(std::string meshName);

protected:

private:
	MeshFactory();
	~MeshFactory();

	std::map<std::string, MeshInfo> LoadedMeshes;

	Mesh3dsLoader mesh3dsLoader;
	MeshXmlLoader xmlMeshLoader;
};

#endif // MeshFactory_h__