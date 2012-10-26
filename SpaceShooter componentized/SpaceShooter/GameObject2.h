/********************************************************************
    created:    26:10:2012   10:44
    filename:   GameObject2.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef GameObject2_h__
#define GameObject2_h__


class GameObject2
{
public:
	GameObject2()
	{
		kill = false;
	}

	virtual ~GameObject2();

	virtual void Update(float deltaTime) = 0;

	virtual void Draw() = 0;

	void FlagForKill(){kill = true;}

	bool CanKill(){return kill;}

protected:

private:
	bool kill;
};

#endif // GameObject2_h__