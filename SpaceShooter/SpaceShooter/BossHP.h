/********************************************************************
    created:    15:11:2012   19:49
    filename:   BossHP.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef BossHP_h__
#define BossHP_h__

#include "GUIEntry.h"
#include "SpaceShipManager.h"
#include "VBODrawable.h"
#include "MeshFactory.h"

class BossHP : public GUIEntry
{
public:
    BossHP();
    ~BossHP();

	void Init();
	void Init(ManagerInterface* manager){}

	void Update(float deltaTime);
	void Draw(VBODrawable* vbo);

protected:

private:
	VBODrawable _vbo;

	float bossHP;
	float bossMaxHP;
	float xScale;
};

#endif // BossHP_h__