/********************************************************************
    created:    9:11:2012   15:57
    filename:   PlayGameEntry.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef PlayGameEntry_h__
#define PlayGameEntry_h__

#include "MenuEntry.h"

class PlayGameEntry : public MenuEntry
{
public:
    PlayGameEntry();
    ~PlayGameEntry();

	virtual void OnClicked();

protected:

private:

};

#endif // PlayGameEntry_h__