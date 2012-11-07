/********************************************************************
    created:    26:10:2012   10:44
    filename:   GameObject2.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef GameObject2_h__
#define GameObject2_h__


class GameObject
{
public:
	GameObject()
	{
		kill = false;
	}

	//virtual ~GameObject2();

	virtual void Update(float deltaTime) = 0;

	virtual void Draw() = 0;

	void FlagForKill(){kill = true;}

	bool CanKill(){return kill;}

	bool IsAlive(){return !kill;}

	void SetOwner(GameObject* owner){this->owner = owner;}
	GameObject* GetOwner(){return owner;}
protected:

private:
	bool kill;
	GameObject* owner;
};

#endif // GameObject2_h__