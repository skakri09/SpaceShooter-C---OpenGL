#include "ScoreValueEntry.h"


ScoreValueEntry::ScoreValueEntry()
{
}

ScoreValueEntry::~ScoreValueEntry()
{
}

void ScoreValueEntry::Init( ManagerInterface* manager )
{
	try
	{
		scoreManager = dynamic_cast<ScoreManager*>(manager);
	}
	catch (const std::bad_cast& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "This object is not of type ScoreManager*" << std::endl;
	}

	displayedScore = scoreManager->GetScore();

	std::stringstream livesStream;
	livesStream << displayedScore;

	stringInUse = livesStream.str();
	updatedString = stringInUse;

	VBOString = TextFactory::Inst()->GetVboString(&stringInUse);

	Vector3D rotAxis(0, 1, 0);
	transformable.Init(3.6f, -3.3f, -5, rotAxis, -15, 0.008f, Vector3D::ZeroVec());
}

void ScoreValueEntry::Update( float deltaTime )
{
	unsigned int currentScore = scoreManager->GetScore();
	if( displayedScore != currentScore)
	{
		displayedScore = currentScore;
		std::stringstream livesStream;
		livesStream << currentScore;
		updatedString = livesStream.str();
	}
	TextEntry::Update(deltaTime);
}

void ScoreValueEntry::Draw(VBODrawable* vbo)
{

	glColor3f(0.898f, 0.694f, 0.227f);
	TextEntry::Draw(vbo);
	glColor3f(1, 1, 1);
}
