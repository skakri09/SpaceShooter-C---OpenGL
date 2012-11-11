/********************************************************************
    created:    10:11:2012   23:30
    filename:   ManagerInterface.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef ManagerInterface_h__
#define ManagerInterface_h__


class ManagerInterface
{
public:
	virtual void Update(float deltaTime) = 0;
};

#endif // ManagerInterface_h__