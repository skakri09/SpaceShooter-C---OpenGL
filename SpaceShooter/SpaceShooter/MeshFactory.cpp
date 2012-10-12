#include "MeshFactory.h"


MeshFactory::MeshFactory()
{
}

MeshFactory::~MeshFactory()
{
}

MeshFactory* MeshFactory::Inst()
{
	static MeshFactory* instance = new MeshFactory();
	return instance;
}

MeshInfo MeshFactory::GetMesh( std::string meshName)
{
	if(LoadedMeshes.find(meshName) != LoadedMeshes.end())
	{
		return LoadedMeshes.find(meshName)->second;
	}
	else
	{		
		std::string meshNameCopy = meshName;
		std::string extensionChars = "";
		char backChar;
		for(char backChar= meshNameCopy.at(meshNameCopy.size()-1); 
			backChar != '.'; 
			backChar = meshNameCopy.at(meshNameCopy.size()-1))
		{
			extensionChars += backChar;
			meshNameCopy.pop_back();
		}
		std::string extension = "";
		while(extensionChars.size() > 0)
		{
			extension += extensionChars.back();
			extensionChars.pop_back();
		}
		if(extension == "3ds")
		{
			//load 3ds file
			LoadedMeshes[meshName] = mesh3dsLoader.Load3dsMesh(meshName);
			return LoadedMeshes[meshName];
		}
		else if(extension == "xml")
		{
			//load xml file
			//LoadedMeshes[meshName] = xmlMeshLoader.LoadMeshXml(meshName);

		}
	}
}
