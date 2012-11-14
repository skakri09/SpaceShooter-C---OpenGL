/********************************************************************
    created:    7:10:2012   12:40
    filename:   ImperialTieInterceptor.h
    author:     Kristian Skarseth
    
    purpose:    An imperial tie interceptor enemy
*********************************************************************/
#ifndef ImperialTieInterceptor_h__
#define ImperialTieInterceptor_h__

#include "BaseEnemyShip.h"
#include "Logger.h"
#include "SpaceShip.h"
#include "PlayerSpaceShip.h"

#include "EnemySpaceshipConstantState.h"
#include "FireState.h"
#include "IdleState.h"
#include "ApproachEdge.h"

class ImperialTieInterceptor : public BaseEnemyShip
{
public:
    ImperialTieInterceptor(std::shared_ptr<PlayerSpaceShip> playerShip);
    virtual ~ImperialTieInterceptor();
	
	void Update(GLfloat deltaTime);
	
	void Draw();

	void InitSpaceShip(float startX, float startY, float startZ,
		float startRotDeg, float rotX, float rotY, float rotZ,
		float dirVecX, float dirVecY, float dirVecZ);

protected:

private:
	Logger log;
};

#endif // ImperialTieInterceptor_h__