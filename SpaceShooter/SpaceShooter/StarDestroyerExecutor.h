/********************************************************************
    created:    15:11:2012   10:24
    filename:   StarDestroyerExecutor.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef StarDestroyerExecutor_h__
#define StarDestroyerExecutor_h__

#include "GameObject.h"
#include "VBODrawable.h"
#include "Transformable.h"
#include "MeshFactory.h"
#include "Texturable.h"

class StarDestroyerExecutor : public GameObject
{
public:
    StarDestroyerExecutor();
    ~StarDestroyerExecutor();

	void Draw();

	void Update(GLfloat deltaTime);



	VBODrawable vboDrawable;
	Transformable transformable;
	Texturable texturable;

protected:

	void Init(float xPos, float yPos, float zPos);
	void LoadAssets();

};

#endif // TStarDestroyerExecutor_h__