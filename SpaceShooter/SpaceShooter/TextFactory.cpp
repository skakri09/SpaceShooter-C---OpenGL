#include "TextFactory.h"


TextFactory::TextFactory()
	:log("TextFactory", WARN)
{
}

TextFactory::~TextFactory()
{
}

TextFactory* TextFactory::Inst()
{
	static TextFactory* instance = new TextFactory();
	return instance;
}

void TextFactory::InitTextFactory()
{
	//Loading all the letters (a-z) and placing in a map
	for(unsigned int i = 97; i < 123; i++)
	{
		std::string baseCharPath = "..//3ds//Text//Alphabet//";
		char letter = static_cast<char>(i);
		baseCharPath += letter;
		baseCharPath += ".3ds";
		alphabet[letter] = MeshFactory::Inst()->GetMesh(baseCharPath);
	}
}


std::shared_ptr<VboString> TextFactory::GetVboString( std::string& text )
{
	std::shared_ptr<VboString> retVec = std::make_shared<VboString>();

	for(std::string::iterator i = text.begin(); i != text.end(); i++)
	{
		VboLetter letter = GetVboLetter(*i);
		
		
		log << WARN << letter.letter << std::endl;
		retVec->push_back(letter);
	}
	return retVec;
}


VboLetter TextFactory::GetVboLetter( char letter )
{
	VboLetter retLetter;

	int intVal = static_cast<int>(letter);
	
	if(intVal == 32) // space
	{
		retLetter.meshInfo = NULL;
		retLetter.letter = ' ';
	}
	else if(intVal < 97 || intVal > 122) // not ascii a-z lowercase
	{
		log << ERRORX << letter << " is not a supported letter. Only lowercase a-z, returning 'a'" << std::endl;
		
		retLetter.meshInfo = &alphabet['a'];
		retLetter.letter = 'a';
	}
	else //Letter is a valid ascii a-z lowercast
	{
		if(alphabet.find(letter) != alphabet.end())
		{
			retLetter.meshInfo = &alphabet.find(letter)->second;
			retLetter.letter = letter;
		}
		else
		{
			log << CRITICAL << "Cannot find letter. " << letter << ". Returning 'a'" << std::endl;
			retLetter.meshInfo = &alphabet['a'];
			retLetter.letter = 'a';
		}
	}
	return retLetter;
}
