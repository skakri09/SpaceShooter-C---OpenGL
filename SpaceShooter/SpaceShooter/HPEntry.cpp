#include "HPEntry.h"


HPEntry::HPEntry()
{
}

HPEntry::~HPEntry()
{

}

void HPEntry::Init()
{
	int hp = SpaceShipManager::Inst()->GetPlayer()->GetSpaceshipHP();
	currentlyDisplayedHP = hp;
	std::stringstream hpStream;
	hpStream << "hp: " << hp;

	stringInUse = hpStream.str();
	updatedString = stringInUse;

	VBOString = TextFactory::Inst()->GetVboString(&stringInUse);

	Vector3D rotation(0, 15, 0);
	transformable.Init(-6.8f, -3.0f, -5, rotation, 0.008f, Vector3D::ZeroVec());
}

void HPEntry::Update(float deltaTime)
{
	int currentHP = SpaceShipManager::Inst()->GetPlayer()->GetSpaceshipHP();
	if( currentlyDisplayedHP != currentHP)
	{
		currentlyDisplayedHP = currentHP;
		std::stringstream hpStream;
		hpStream << "hp: " << currentHP;
		updatedString = hpStream.str();
	}
	TextEntry::Update(deltaTime);
}

void HPEntry::Draw(VBODrawable* vbo)
{
	float g = static_cast<float>(currentlyDisplayedHP)/50;
	float r = static_cast<float>(50-currentlyDisplayedHP)/50;
	glColor3f(r, g, 0);
	TextEntry::Draw(vbo);
	glColor3f(1, 1, 1);
}

