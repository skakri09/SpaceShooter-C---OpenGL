/********************************************************************
created:    10:10:2012   14:20
filename:   Image.h
author:     Kristian Skarseth

purpose:    
*********************************************************************/
#ifndef Image_h__
#define Image_h__

#include <vector>

class Image
{
public:
	std::vector<char> data;
	unsigned int components;
	unsigned long width;
	unsigned long height;
};

#endif // Image_h__