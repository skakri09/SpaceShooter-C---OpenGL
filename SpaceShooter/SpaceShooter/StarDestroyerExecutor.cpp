#include "StarDestroyerExecutor.h"

StarDestroyerExecutor::StarDestroyerExecutor()
{
	Init(-850, -50, -800);
}

StarDestroyerExecutor::~StarDestroyerExecutor()
{

}

void StarDestroyerExecutor::Draw()
{
	glPushMatrix();
	transformable.ApplyGLTransformations(true, true, false);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-15, 1, 0, 0);
	texturable.BindTexture("DSP");
	vboDrawable.Draw();

	texturable.UnbindTexture();
	glPopMatrix();
}

void StarDestroyerExecutor::Update( GLfloat deltaTime )
{
	//up-down
}

void StarDestroyerExecutor::Init( float xPos, float yPos, float zPos )
{
	LoadAssets();
	transformable.Init(xPos, yPos, zPos, Vector3D::ZeroVec(), 0, 0.5f, Vector3D::ZeroVec());
}

void StarDestroyerExecutor::LoadAssets()
{
	if(!vboDrawable.HaveMeshInfo())
	{
		std::shared_ptr<MeshInfo> meshInfo = MeshFactory::Inst()->GetMesh("..//3ds//StarDestroyerExecutor//StarDestroyerExecutor.3ds");
		vboDrawable.SetMeshInfo(meshInfo);
	}
	texturable.InitTexture("..//3ds//StarDestroyerExecutor//Aluminm_grey.jpg", "DSP");
}

