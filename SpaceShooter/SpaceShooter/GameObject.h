/********************************************************************
    created:    26:10:2012   10:44
    filename:   GameObject2.h
    author:     Kristian Skarseth
    
    purpose:    A base GameObject. It's an abstract object used as base
				for all gameobjects in the game.
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

	virtual void Update(float deltaTime) = 0;

	virtual void Draw() = 0;

	void FlagForKill(){kill = true;}

	bool CanKill(){return kill;}

	bool IsAlive(){return !kill;}

	//Sets a pointer to another GameObject that is stored in this GameObject.
	//This reference can be retrieved with GetOwner
	void SetOwner(GameObject* owner){this->owner = owner;}

	//Returns locally stored pointer to the GameObject that has been set with SetOwner
	GameObject* GetOwner(){return owner;}

	//Compares the address of this and another gameObject to see
	//if they are the same. 
	bool operator==(GameObject& otherGameObj)
	{
		if(&otherGameObj == this)
		{
			return true;
		}
		return false;
	}

protected:
	bool kill;
private:
	
	GameObject* owner;
};

#endif // GameObject2_h__