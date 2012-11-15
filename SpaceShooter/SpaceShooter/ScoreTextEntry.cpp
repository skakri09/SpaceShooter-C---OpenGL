#include "ScoreTextEntry.h"


ScoreTextEntry::ScoreTextEntry()
{
}

ScoreTextEntry::~ScoreTextEntry()
{
}

void ScoreTextEntry::Init()
{
	updatedString = stringInUse = "score:";
	
	VBOString = TextFactory::Inst()->GetVboString(&stringInUse);

	Vector3D rotation(0, -15, 0);
	transformable.Init(3.6f, -2.8f, -5, rotation, 0.008f, Vector3D::ZeroVec());
}

void ScoreTextEntry::Update( float deltaTime )
{
	TextEntry::Update(deltaTime);
}

void ScoreTextEntry::Draw(VBODrawable* vbo)
{
	glColor3f(0.898f, 0.694f, 0.227f);
	TextEntry::Draw(vbo);
	glColor3f(1, 1, 1);
}
