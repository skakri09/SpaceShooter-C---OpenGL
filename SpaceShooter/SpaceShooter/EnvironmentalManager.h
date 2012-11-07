/********************************************************************
    created:    7:11:2012   18:25
    filename:   EnvironmentalManager.h
    author:     Kristian Skarseth
    
    purpose:    Manager to control environmental gameobjects etc
*********************************************************************/
#ifndef EnvironmentalManager_h__
#define EnvironmentalManager_h__

#include "Planet.h"
#include "MeshFactory.h"

class EnvironmentalManager
{
public:
    EnvironmentalManager();
    ~EnvironmentalManager();

	void InitManager();

	void Update(float deltaTime);
	
	void DrawEnvironment();
protected:

private:
	Planet planet;
};

#endif // EnvironmentalManager_h__