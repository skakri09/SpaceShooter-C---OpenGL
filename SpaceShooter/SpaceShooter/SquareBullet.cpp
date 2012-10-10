#include "SquareBullet.h"

SquareBullet::SquareBullet() : Projectile(5.0f)
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
		//displayList = glGenLists(1);
		
		std::shared_ptr<Mesh> mesh = meshLoader.LoadMeshXml("Mesh_SquareBullet.xml");
		
		collisionSphere.CreateCollisionBox(*mesh);

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

		/*MeshInfo meshInfo;
		meshInfo.vertices = meshInfo.vertices;
		meshInfo.indices = meshInfo.indices;
		meshInfo.normals = meshInfo.normals;*/

		ProjectileFactory::Inst()->AddVBOInfo(SIMPLE_BULLET, meshInfo);
		//glNewList(displayList, GL_COMPILE);
		//glBegin(GL_QUADS);
		//
		////front square
		//glNormal3f(0.0f, 0.0f, 1.0f);
		//glVertex3f(-0.5f, 0.0f, 0.0f);
		//glVertex3f(0.5f, 0.0f, 0.0f);
		//glVertex3f(0.5f, 1.0f, 0.0f);
		//glVertex3f(-0.5f, 1.0f, 0.0f);

		////right square
		//glNormal3f(1.0f, 0.0f, 0.0f);
		//glVertex3f(0.5f, 0.0f, 0.0f);
		//glVertex3f(0.5f, 0.0f, -3.0f);
		//glVertex3f(0.5f, 1.0f, -3.0f);
		//glVertex3f(0.5f, 1.0f, 0.0f);

		////back square
		//glNormal3f(0.0f, 0.0f, -1.0f);
		//glVertex3f(0.5f, 0.0f, -3.0f);
		//glVertex3f(-0.5f, 0.0f, -3.0f);
		//glVertex3f(-0.5f, 1.0f, -3.0f);
		//glVertex3f(0.5f, 1.0f, -3.0f);

		////left square
		//glNormal3f(-1.0f, 0.0f, 0.0f);
		//glVertex3f(-0.5f, 0.0f, -3.0f);
		//glVertex3f(-0.5f, 0.0f, 0.0f);
		//glVertex3f(-0.5f, 1.0f, 0.0f);
		//glVertex3f(-0.5f, 1.0f, -3.0f);

		////top square
		//glNormal3f(0.0f, 1.0f, 0.0f);
		//glVertex3f(-0.5f, 1.0f, 0.0f);
		//glVertex3f(0.5f, 1.0f, 0.0f);
		//glVertex3f(0.5f, 1.0f, -3.0f);
		//glVertex3f(-0.5f, 1.0f, -3.0f);

		////bottom square
		//glNormal3f(0.0f, -1.0f, 0.0f);
		//glVertex3f(-0.5f, 0.0f, 0.0f);
		//glVertex3f(-0.5f, 0.0f, -3.0f);
		//glVertex3f(0.5f, 0.0f, -3.0f);
		//glVertex3f(0.5f, 0.0f, 0.0f);

		//glEnd();
		//glEndList();
	}	
	else
	{
		meshInfo = *_meshInfo;
	}
}


