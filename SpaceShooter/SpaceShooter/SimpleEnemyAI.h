/********************************************************************
    created:    7:10:2012   9:45
    filename:   SimpleEnemyAI.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef SimpleEnemyAI_h__
#define SimpleEnemyAI_h__

#include "SimpleEnemyShip.h"

class SimpleEnemyShip;
class SimpleEnemyAI
{
public:
    SimpleEnemyAI();
    ~SimpleEnemyAI();

	void UpdateAI(SimpleEnemyShip* ship);

protected:

private:

};

#endif // SimpleEnemyAI_h__