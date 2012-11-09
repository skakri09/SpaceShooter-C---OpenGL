/********************************************************************
    created:    9:11:2012   15:05
    filename:   TextFactory.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef TextFactory_h__
#define TextFactory_h__

#include <string>
#include <map>
#include <memory>

#include "Logger.h"
#include "MeshFactory.h"
#include "Transformable.h"
#include "VBODrawable.h"

struct VboLetter
{
	Transformable stringPosition;
	std::shared_ptr<MeshInfo> meshInfo;
	char letter;
};

typedef std::vector<VboLetter> VboString;

class TextFactory
{
public:
    static TextFactory* Inst();

	void InitTextFactory();

	//Returns a vector of VboLeteters made out of the parameter string.
	//Each VboLetter has a letter specific position to be used as string 
	//offset, a meshinfo pointer for each specific letter, and a char to 
	//identify the letter the VboLetter represents
	std::shared_ptr<VboString> GetVboString(std::string& text);

protected:

private:
	TextFactory();
	~TextFactory();

	Logger log;


	std::map<char, std::shared_ptr<MeshInfo>> alphabet;

	//Retrieves a character from the alphabet map
	VboLetter GetVboLetter(char letter);
};

#endif // TextFactory_h__