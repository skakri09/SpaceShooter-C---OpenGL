#include "StarDestroyerExecutor.h"

StarDestroyerExecutor::StarDestroyerExecutor()
{
	Init(-850, -15, -800);
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
	transformable.Update(deltaTime);

	float dist = transformable.getPosition()->Distance(*target);
	if(dist <= 10)
	{
		Vector3D newVel = orgVel;
		newVel *= dist/10;
		transformable.SetVelocity(newVel);
		if(dist <= 2)
		{	
			orgVel.InvertY();
			transformable.setYVel(orgVel.getY()/10);
			if(bottomIsTarget)
			{
				target = &tTarPos;
				bottomIsTarget = false;
			}
			else
			{
				target = &bTarPos;
				bottomIsTarget = true;
			}
		}
	}
	else
	{
		if(!bottomIsTarget)
		{
			if(transformable.getYVel() < orgVel.getY())
			{
				transformable.setYVel(transformable.getYVel()+5*deltaTime);
			}
		}
		else
		{
			if(transformable.getYVel() > orgVel.getY())
			{
				transformable.setYVel(transformable.getYVel()-5*deltaTime);
			}
		}
	}
}

void StarDestroyerExecutor::Init( float xPos, float yPos, float zPos )
{
	LoadAssets();
	transformable.Init(xPos, yPos, zPos, Vector3D::ZeroVec(), 0, 0.5f, Vector3D::ZeroVec());
	
	tTarPos = *transformable.getPosition();

	bTarPos = tTarPos;
	bTarPos.setY(-75);
	
	transformable.setYVel(-5);
	orgVel = *transformable.getVelocity();
	target = &bTarPos;
	downIsTarget = true;

}

void StarDestroyerExecutor::LoadAssets()
{
	if(!vboDrawable.HaveMeshInfo())
	{
		std::shared_ptr<MeshInfo> meshInfo = MeshFactory::Inst()->GetMesh("..//3ds//StarDestroyerExecutor//StarDestroyerExecutor.3ds");
		vboDrawable.SetMeshInfo(meshInfo);
	}
	texturable.InitTexture("..//3ds//StarDestroyerExecutor//dark_panels.jpg", "DSP");
}
