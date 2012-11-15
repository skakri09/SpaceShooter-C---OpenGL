/********************************************************************
    created:    7:11:2012   18:25
    filename:   EnvironmentalManager.h
    author:     Kristian Skarseth
    
    purpose:    Manager to control environmental gameobjects etc
*********************************************************************/
#ifndef EnvironmentalManager_h__
#define EnvironmentalManager_h__

#include <vector>

#include "Planet.h"
#include "MeshFactory.h"
#include "ManagerInterface.h"
#include "DeathStar.h"
#include "StarDestroyerExecutor.h"

class EnvironmentalManager : public ManagerInterface
{
public:
    EnvironmentalManager();
    ~EnvironmentalManager();

	void InitManager();

	void Update(float deltaTime);
	
	void DrawEnvironment();

	void ResetEnvironment();

protected:

private:
	std::vector<std::shared_ptr<GameObject>> Environment;
};

#endif // EnvironmentalManager_h__