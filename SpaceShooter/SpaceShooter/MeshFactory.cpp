#include "MeshFactory.h"


MeshFactory::MeshFactory()
	:log("MeshFactory", WARN)
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

std::shared_ptr<MeshInfo> MeshFactory::GetMesh( std::string meshName)
{
	if(LoadedMeshes.find(meshName) != LoadedMeshes.end())
	{
		return LoadedMeshes.find(meshName)->second;
	}
	else
	{		
		std::string extension = GetExtension(meshName);
		if(extension == "3ds")
		{
			//load 3ds file
			LoadedMeshes[meshName] = std::make_shared<MeshInfo>();
			*LoadedMeshes[meshName] = mesh3dsLoader.Load3dsMesh(meshName);

			return LoadedMeshes[meshName];
		}
		else if(extension == "xml")
		{
			//load xml file
			LoadedMeshes[meshName] = std::make_shared<MeshInfo>();
			*LoadedMeshes[meshName] = xmlMeshLoader.LoadMeshXml(meshName);
			return LoadedMeshes[meshName]; 
		}
	}
	return std::make_shared<MeshInfo>();
}

void MeshFactory::LoadMesh( std::string meshName )
{
	if(LoadedMeshes.find(meshName) != LoadedMeshes.end())
	{
		log << INFO << meshName << " has already been loaded" << std::endl;
	}
	else
	{
		std::string extension = GetExtension(meshName);
		if(extension == "3ds")
		{
			//load 3ds file
			LoadedMeshes[meshName] = std::make_shared<MeshInfo>();
			*LoadedMeshes[meshName] = mesh3dsLoader.Load3dsMesh(meshName);
		}
		else if(extension == "xml")
		{
			//load xml file
			LoadedMeshes[meshName] = std::make_shared<MeshInfo>();
			*LoadedMeshes[meshName] = xmlMeshLoader.LoadMeshXml(meshName);
		}
	}
}

std::string MeshFactory::GetExtension( std::string& filePath )
{
	std::string meshNameCopy = filePath;
	std::string extensionChars = "";
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
	return extension;
}
