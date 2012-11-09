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


std::shared_ptr<VboString> TextFactory::GetVboString( std::string* text )
{
	std::shared_ptr<VboString> retString = std::make_shared<VboString>();

	//Making sure the string is completely lowercase as 
	//we only support lowercase ascii a-z
	std::transform(text->begin(), text->end(), text->begin(), ::tolower);

	Vector3D position(0.0f, 0.0f, 0.0f);
	int nextLetterAdjustment = 0;
	retString->stringLength = 0.0f;
	for(std::string::iterator i = text->begin(); i != text->end(); i++)
	{
		if(*i == '\n')
		{	//Moving line down
			position.setY(position.getY()-60);
			position.setX(0.0f);
			continue;
		}
		VboLetter letter = GetVboLetter(*i);
	
		if(letter.letter == 'i')
		{
			retString->stringLength += (40+nextLetterAdjustment);
			position.setX((position.getX()+40+nextLetterAdjustment));
			nextLetterAdjustment = -10;
		}
		else if(letter.letter == 'j')
		{
			retString->stringLength += (40+nextLetterAdjustment);
			position.setX((position.getX()+40+nextLetterAdjustment));
			nextLetterAdjustment = -10;
		}
		else if(letter.letter == 'w')
		{
			retString->stringLength += (60+nextLetterAdjustment);
			position.setX((position.getX()+60+nextLetterAdjustment));
			nextLetterAdjustment = 10;
		}
		else if(letter.letter == 'v')
		{
			retString->stringLength += (55+nextLetterAdjustment);
			position.setX((position.getX()+55+nextLetterAdjustment));
			nextLetterAdjustment = 5;
		}
		else if(letter.letter == 'x')
		{
			retString->stringLength += (55+nextLetterAdjustment);
			position.setX((position.getX()+55+nextLetterAdjustment));
			nextLetterAdjustment = 5;
		}
		else if(letter.letter == 'y')
		{
			retString->stringLength += (55+nextLetterAdjustment);
			position.setX((position.getX()+55+nextLetterAdjustment));
			nextLetterAdjustment = 5;
		}
		else if(letter.letter == 'c')
		{
			retString->stringLength += (55+nextLetterAdjustment);
			position.setX((position.getX()+55+nextLetterAdjustment));
			nextLetterAdjustment = 5;
		}
		else if(letter.letter == 'q')
		{
			retString->stringLength += (50+nextLetterAdjustment);
			position.setX((position.getX()+50+nextLetterAdjustment));
			nextLetterAdjustment = 5;
		}
		else if(letter.letter == 'm')
		{
			retString->stringLength += (55+nextLetterAdjustment);
			position.setX((position.getX()+55+nextLetterAdjustment));
			nextLetterAdjustment = 5;
		}
		else if(letter.letter != ' ')
		{
			retString->stringLength += (50+nextLetterAdjustment);
			position.setX((position.getX()+50+nextLetterAdjustment));
			nextLetterAdjustment = 0;
		}
		else //Space
		{
			position.setX(position.getX() + 30);
			retString->stringLength += 30;
			continue;
		}

		letter.stringPosition.Init(position, 1, Vector3D::ZeroVec());

		retString->vboLetters.push_back(letter);
	}
	
	return retString;
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
		
		retLetter.meshInfo = alphabet['a'];
		retLetter.letter = 'a';
	}
	else //Letter is a valid ascii a-z lowercast
	{
		if(alphabet.find(letter) != alphabet.end())
		{
			retLetter.meshInfo = alphabet.find(letter)->second;
			retLetter.letter = letter;
		}
		else
		{
			log << CRITICAL << "Cannot find letter. " << letter << ". Returning 'a'" << std::endl;
			retLetter.meshInfo = alphabet['a'];
			retLetter.letter = 'a';
		}
	}
	return retLetter;
}
