#include "XmlLoader.h"


XmlLoader::XmlLoader()
{

}

XmlLoader::~XmlLoader()
{

}

std::shared_ptr<ptree> XmlLoader::LoadXML( std::string xmlFilePath )
{
	std::shared_ptr<ptree> xmlPtree = std::make_shared<ptree>();

	read_xml(xmlFilePath, *xmlPtree);

	return xmlPtree;
}
