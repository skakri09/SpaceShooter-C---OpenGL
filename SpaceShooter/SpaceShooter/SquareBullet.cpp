#include "SquareBullet.h"

SquareBullet::SquareBullet() : Projectile(5.0f, 10)
{
	CreateDrawable();
}

SquareBullet::~SquareBullet()
{
}

void SquareBullet::CreateDrawable()
{
	MeshInfo* _meshInfo = ProjectileFactory::Inst()->GetMeshInfo(SIMPLE_BULLET);

	if(_meshInfo == NULL)
	{	
		std::shared_ptr<Mesh> mesh = meshLoader.LoadMeshXml("Mesh_SquareBullet.xml");
		meshInfo.numberOfIndices = mesh->indices.size();

		meshInfo.collisionSphere = std::make_shared<BoundingSphere>();
		meshInfo.collisionSphere->CreateCollisionBox(*mesh);
		collisionSphere = *meshInfo.collisionSphere;
		glGenBuffers(1, &meshInfo.vertices);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &meshInfo.normals);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*mesh->normals.size(), &mesh->normals[0], GL_STATIC_DRAW);

		/*glGenBuffers(1, &colors);
		glBindBuffer(GL_COLOR_ARRAY, colors);
		glBufferData(GL_COLOR_ARRAY, sizeof(float)*mesh->colors.size(), &mesh->colors[0], GL_STATIC_DRAW);*/

		glGenBuffers(1, &meshInfo.indices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*mesh->indices.size(), &mesh->indices[0], GL_STATIC_DRAW);


		ProjectileFactory::Inst()->AddVBOInfo(SIMPLE_BULLET, meshInfo);

	}	
	else
	{
		meshInfo = *_meshInfo;
		collisionSphere = *_meshInfo->collisionSphere;
	}
}


