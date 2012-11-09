#include "Mesh3dsLoader.h"


Mesh3dsLoader::Mesh3dsLoader()
	:log("Mesh3dsLoader", WARN)
{
}

Mesh3dsLoader::~Mesh3dsLoader()
{
	if(model != NULL)
	{
		lib3ds_file_free(model);

	}
}

MeshInfo Mesh3dsLoader::Load3dsMesh( std::string _3dsMeshFile )
{
	model = lib3ds_file_load(_3dsMeshFile.c_str());
	
	MeshInfo meshInfo;

	Lib3dsMaterial* foo = model->materials;
	//Lib3dsMaterial* lib3ds_file_get_materials(Lib3dsFile *file) { return file->materials; }

	if(!model)
	{
		log << ERRORX << "Unable to load: " << _3dsMeshFile << std::endl;
	}
	else
	{
		//Getting the number of faces so that we can reserve space
		//in the vectors for the correct amount, as the size could
		//be really big and it sucks to move it all around in memory.
		totalFaces = GetNrOfFaces();

		Lib3dsVector* vertices = new Lib3dsVector[totalFaces * 3];
		//Lib3dsTexel* texCoords = new Lib3dsTexel[totalFaces * 3];
		Lib3dsVector* normals = new Lib3dsVector[totalFaces * 3];


		Lib3dsMesh* mesh;
		unsigned int finishedFaces = 0;

		for(mesh = model->meshes; mesh != NULL; mesh = mesh->next)
		{
			lib3ds_mesh_calculate_normals(mesh, &normals[finishedFaces*3]);
			
			for(unsigned int currentFace = 0; currentFace < mesh->faces; currentFace++)
			{
				Lib3dsFace* face = &mesh->faceL[currentFace];
				for(unsigned int i = 0; i  < 3; i++)
				{
					//if(mesh->texelL)
					//{	//copying the texcoords. This is not finished yet, and not sure if working
					//	memcpy(&texCoords[finishedFaces*3 +i], mesh->texelL[face->points[i]], sizeof(float)*2);
					//	log << INFO << mesh->faceL[i].material << std::endl;
					//}
					memcpy(&vertices[finishedFaces*3 +i], mesh->pointL[face->points[i]].pos, sizeof(float)*3);
				}
				finishedFaces++;
			}
		}

		meshInfo.mode = GL_TRIANGLES;
		//Creating the buffer objects
		meshInfo.haveVertices = true;
		glGenBuffers(1, &meshInfo.vertices);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * totalFaces, &vertices[0], GL_STATIC_DRAW);

		meshInfo.haveNormals = true;
		glGenBuffers(1, &meshInfo.normals);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * totalFaces, &normals[0], GL_STATIC_DRAW);

		//meshInfo.haveTexCoords = true;
		//glGenBuffers(1, &meshInfo.textCoords);
		//glBindBuffer(GL_ARRAY_BUFFER, meshInfo.textCoords);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsTexel) * 2 * totalFaces, &texCoords[0], GL_STATIC_DRAW);
		
		meshInfo.numberOfIndices = totalFaces*3;

		collisionSphere = std::make_shared<BoundingSphere>();
		collisionSphere->CreateCollisionBox(vertices, totalFaces);
		meshInfo.collisionSphere = collisionSphere;
		if(vertices)
		{
			delete[] vertices;
		}
		if(normals)
		{
			delete[] normals;
		}
		/*if(texCoords)
		{
			delete[] texCoords;
		}*/
		
		//Since we have created the VBOs we can free the model
		lib3ds_file_free(model);
		model = NULL; 

		return meshInfo;
	}
	return meshInfo;
}


unsigned int Mesh3dsLoader::GetNrOfFaces()
{
	assert(model != NULL);

	unsigned int returnVal = 0;
	Lib3dsMesh* mesh;
	
	for(mesh = model->meshes; mesh != NULL; mesh = mesh->next)
	{
		returnVal += mesh->faces;
	}
	
	if(mesh)//Just in case something funky would happen
	{
		delete mesh;
		mesh = NULL;
	}

	return returnVal;
}

