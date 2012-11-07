#ifndef GetRandomFloat_H
#define GetRandomFloat_H

#include <cstdlib>

//Returns a random float between the min and max parameter
static float GetRandFloat( float min, float max )
{
	return ((max - min) * ((float)rand()/RAND_MAX))+min;
}

#endif // GetRandomFloat_H

