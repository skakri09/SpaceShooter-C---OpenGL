#include "ApproachEdge.h"


void ApproachEdge::Enter( BaseEnemyShip* owner )
{
	log << INFO << "Entering ApproachEdge state" << std::endl;

}

void ApproachEdge::UpdateState( BaseEnemyShip* owner, float deltaTime )
{
	

}

void ApproachEdge::Exit( BaseEnemyShip* owner )
{
	log << INFO << "Exiting ApproachEdge state" << std::endl;
}
