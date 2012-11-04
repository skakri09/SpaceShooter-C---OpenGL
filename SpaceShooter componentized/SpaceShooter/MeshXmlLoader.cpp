#include "MeshXmlLoader.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;

MeshXmlLoader::MeshXmlLoader()
	:log("MeshLoader", WARN)
{
}

MeshXmlLoader::~MeshXmlLoader()
{
}

MeshInfo MeshXmlLoader::LoadMeshXml( std::string meshLoadPath )
{
	MeshInfo meshInfo;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	std::vector<float> colors;
	std::vector<unsigned int> texCoords;
	
	//Loading the xml with base class' xml loader function
	ptree xmlPtree = *XmlLoader::LoadXML(meshLoadPath);
	
	std::string verticesString = xmlPtree.get<std::string>("mesh.vertices");
	if(!PlaceFloatsInMeshObj(verticesString, vertices))
	{
		log << ERRORX << "The placing of vertices in mesh object was not successful" << std::endl;
	}
	
	std::string indicesString = xmlPtree.get<std::string>("mesh.indices");
	if(!PlaceUIntsInMeshObj(indicesString, indices))
	{
		log << ERRORX << "The placing of indices in mesh object was not successful" << std::endl;
	}
	
	std::string colorsString = xmlPtree.get<std::string>("mesh.colors");
	if(!PlaceFloatsInMeshObj(colorsString, colors))
	{
		log << ERRORX << "The placing of indices in mesh object was not successful" << std::endl;
	}

	std::string texCoordString = xmlPtree.get<std::string>("mesh.textCoords");
	if(!PlaceUIntsInMeshObj(texCoordString, texCoords))
	{
		log << ERRORX << "The placing of texCoords in mesh object was not successful" << std::endl;
	}

	if(!MakeNormals(vertices, indices, normals))
	{
		log << ERRORX << "The creation of normals was not successful" << std::endl;
	}

	int mode = xmlPtree.get<int>("mesh.mode");
	switch(mode)
	{
	case 3: meshInfo.mode = GL_TRIANGLES;
	case 4: meshInfo.mode = GL_QUADS;
	}
	
	BindVertices(vertices, meshInfo);
	BindNormals(normals, meshInfo);
	BindColors(colors, meshInfo);
	if(BindIndices(indices, meshInfo)){
		meshInfo.numberOfIndices = indices.size();
	}else{
		meshInfo.numberOfIndices = vertices.size();
	}
	BindTexCoords(texCoords, meshInfo);

	

	collisionSphere = std::make_shared<BoundingSphere>();
	collisionSphere->CreateCollisionBox(&vertices);
	meshInfo.collisionSphere = collisionSphere;

 	return meshInfo;
}

bool MeshXmlLoader::PlaceFloatsInMeshObj( std::string& string,
							  std::vector<float>& targetVector  )
{
	//our return value
	bool successful = true;

	//The called function clips the param string into separate values 
	//and insert them in the stringVec.
	std::vector<std::string> stringVec;
	GetStringAsVector(string, stringVec);

	//Looping trough the string vector, removing the ',' char at the end of all
	//the "floats" that has one. Then placing the value in the param vector
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


bool MeshXmlLoader::PlaceUIntsInMeshObj( std::string& stringWithUInts, 
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


void MeshXmlLoader::GetStringAsVector( std::string& originString, std::vector<std::string>& targetVector )
{
	std::istringstream iss(originString);
	copy(std::istream_iterator<std::string>(iss),std::istream_iterator<std::string>(),
		std::back_inserter<std::vector<std::string>>(targetVector));
}


bool MeshXmlLoader::MakeNormals( const std::vector<float>& vertices, 
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

bool MeshXmlLoader::BindVertices( std::vector<float>& vertices, MeshInfo& meshInfo )
{
	if(!vertices.empty())
	{
		meshInfo.haveVertices = true;
		glGenBuffers(1, &meshInfo.vertices);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
		return true;
	}
	else
	{
		log<<INFO<< "there are no vertices in this VBO" << std::endl;
		return false;
	}
}

bool MeshXmlLoader::BindNormals( std::vector<float>& normals, MeshInfo& meshInfo )
{
	if(!normals.empty())
	{
		meshInfo.haveNormals = true;
		glGenBuffers(1, &meshInfo.normals);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
		return true;
	}
	else
	{
		log<<INFO<< "there are no normals in this VBO" << std::endl;
		return false;
	}
}

bool MeshXmlLoader::BindColors( std::vector<float>& colors, MeshInfo& meshInfo )
{
	if(!colors.empty())
	{
		meshInfo.haveColors = true;
		glGenBuffers(1, &meshInfo.colors);
		glBindBuffer(GL_COLOR_ARRAY, meshInfo.colors);
		glBufferData(GL_COLOR_ARRAY, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
		return true;
	}
	else
	{
		log<<INFO<< "there are no colors in this VBO" << std::endl;
		return false;
	}
}

bool MeshXmlLoader::BindIndices( std::vector<unsigned int>& indices, MeshInfo& meshInfo )
{
	if(!indices.empty())
	{
		meshInfo.haveIndices = true;
		glGenBuffers(1, &meshInfo.indices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*indices.size(), &indices[0], GL_STATIC_DRAW);
		return true;
	}
	else
	{
		log<<INFO<< "there are no indices in this VBO" << std::endl;
		return false;
	}
}

bool MeshXmlLoader::BindTexCoords( std::vector<unsigned int>& texCoords, MeshInfo& meshInfo )
{
	if(!texCoords.empty())
	{
		meshInfo.haveTexCoords = true;
		glGenBuffers(1, &meshInfo.textCoords);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.textCoords);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
		return true;
	}
	else
	{
		log<<INFO<< "there are no texCoords in this VBO" << std::endl;
		return false;
	}
}

