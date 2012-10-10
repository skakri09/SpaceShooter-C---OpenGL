#include "MeshLoader.h"


MeshLoader::MeshLoader()
	:log("MeshLoader", WARN)
{
}

MeshLoader::~MeshLoader()
{
}

std::shared_ptr<Mesh> MeshLoader::LoadMeshXml( std::string meshLoadPath )
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	
	//Loading the xml with base class' xml loader function
	ptree xmlPtree = *XmlLoader::LoadXML(meshLoadPath);

	std::string vertices = xmlPtree.get<std::string>("mesh.vertices");
	if(!PlaceFloatsInMeshObj(vertices, mesh->vertices))
	{
		log << ERRORX << "The placing of vertices in mesh object was not successful" << std::endl;
	}
	
	std::string indices = xmlPtree.get<std::string>("mesh.indices");
	if(!PlaceUIntsInMeshObj(indices, mesh->indices))
	{
		log << ERRORX << "The placing of indices in mesh object was not successful" << std::endl;
	}
	
	std::string colors = xmlPtree.get<std::string>("mesh.colors");
	if(!PlaceFloatsInMeshObj(colors, mesh->colors))
	{
		log << ERRORX << "The placing of indices in mesh object was not successful" << std::endl;
	}

	if(!MakeNormals(mesh->vertices, mesh->indices, mesh->normals))
	{
		log << ERRORX << "The creation of normals was not successful" << std::endl;
	}

	return mesh;
}

bool MeshLoader::PlaceFloatsInMeshObj( std::string& string,
							  std::vector<float>& targetVector  )
{
	//our return value
	bool successful = true;

	//The called function clips the param string into separate values 
	//and insert them in the stringVec.
	std::vector<std::string> stringVec;
	GetStringAsVector(string, stringVec);

	//Looping trough the string vector, removing the ',' char at the end of all
	//the "floats" that has one. Then placing the value in the vector we 
	//are returning. Showing a warning if the convertion failed
	for(unsigned int i = 0; i < stringVec.size(); i++)
	{
		if(stringVec.at(i).back() == ',')
		{
			stringVec.at(i).pop_back();
		}

		float targetFloat;
		if(stringToT<float>(targetFloat, stringVec.at(i), std::dec))
		{
			targetVector.push_back(targetFloat);
		}
		else
		{
			successful = false;
			log << ERRORX << "Converting string at " << i 
				<< " failed, not a valid float" << std::endl;
		}
	}
	return successful;
}


bool MeshLoader::PlaceUIntsInMeshObj( std::string& stringWithUInts, 
									std::vector<unsigned int>& targetVector  )
{
	//our return value
	bool successful = true;

	//The called function clips the param string into separate values 
	//and insert them in the stringVec.
	std::vector<std::string> stringVec;
	GetStringAsVector(stringWithUInts, stringVec);

	//Looping trough the string vector, removing the ',' char at the end of all
	//the "unsigned ints" that has one. Then placing the value in the vector we 
	//are returning. Showing a warning if the convertion failed
	for(unsigned int i = 0; i < stringVec.size(); i++)
	{
		if(stringVec.at(i).back() == ',')
		{
			stringVec.at(i).pop_back();
		}
		unsigned int targetUint;
		if(stringToT<unsigned int>(targetUint, stringVec.at(i), std::dec))
		{
			targetVector.push_back(targetUint);
		}
		else
		{
			successful = false;
			log << ERRORX << "Converting string at " << i 
				<< " failed, not a valid unsigned int" << std::endl;
		}
	}
	
	return successful;
}


void MeshLoader::GetStringAsVector( std::string& originString, std::vector<std::string>& targetVector )
{
	std::istringstream iss(originString);
	copy(std::istream_iterator<std::string>(iss),std::istream_iterator<std::string>(),
		std::back_inserter<std::vector<std::string>>(targetVector));
}


bool MeshLoader::MakeNormals( const std::vector<float>& vertices, 
							  const std::vector<unsigned int>& indices, 
							  std::vector<float>& targetVector )
{
	bool successful = true;

	for(unsigned int i = 0; i < indices.size();)
	{
		Vector3D vertex1( vertices.at( indices.at(i) ), vertices.at( indices.at(i) +1 ), vertices.at( indices.at(i) +2 ) );
		Vector3D vertex2( vertices.at(indices.at(i+1) ), vertices.at(indices.at(i+1) +1 ), vertices.at(indices.at(i+1)+2) );
		Vector3D vertex3( vertices.at(indices.at(i+2) ), vertices.at(indices.at(i+2) +1 ), vertices.at(indices.at(i+2)+2) );


		Vector3D normal = normalCalculator.CalculateNormal(&vertex1, &vertex2, &vertex3);
		targetVector.push_back(normal.getX());
		targetVector.push_back(normal.getY());
		targetVector.push_back(normal.getZ());
		i+=3;
	}

	return successful;
}

