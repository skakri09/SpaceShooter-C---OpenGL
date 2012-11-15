#include "LivesEntry.h"


LivesEntry::LivesEntry()
{
}

LivesEntry::~LivesEntry()
{
}

void LivesEntry::Init()
{
	currentlyDisplayedLives = SpaceShipManager::Inst()->GetPlayer()->GetLives();

	std::stringstream livesStream;
	livesStream << "lives: " << currentlyDisplayedLives;

	stringInUse = livesStream.str();
	updatedString = stringInUse;

	VBOString = TextFactory::Inst()->GetVboString(&stringInUse);

	Vector3D rotation(0, 15, 0);
	transformable.Init(-6.8f, -3.7f, -5, rotation, 0.008f, Vector3D::ZeroVec());
}

void LivesEntry::Update( float deltaTime )
{
	int currentLives = SpaceShipManager::Inst()->GetPlayer()->GetLives();
	if( currentlyDisplayedLives != currentLives)
	{
		currentlyDisplayedLives = currentLives;
		std::stringstream livesStream;
		livesStream << "lives: " << currentLives;
		updatedString = livesStream.str();
	}
	TextEntry::Update(deltaTime);
}

void LivesEntry::Draw(VBODrawable* vbo)
{
	float g = static_cast<float>(currentlyDisplayedLives)/3;
	float r = static_cast<float>(3-currentlyDisplayedLives)/3;
	glColor3f(r, g, 0);
	TextEntry::Draw(vbo);
	glColor3f(1, 1, 1);
}
