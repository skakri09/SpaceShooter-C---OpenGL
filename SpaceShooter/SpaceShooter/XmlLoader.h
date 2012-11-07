/********************************************************************
    created:    8:10:2012   9:48
    filename:   XmlLoader.h
    author:     Kristian Skarseth
    
    purpose:    Loads an XML file into a Boost Ptree and returns a
				shared ptr to the ptree.
*********************************************************************/
#ifndef XmlLoader_h__
#define XmlLoader_h__


#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <memory>

using boost::property_tree::ptree;

class XmlLoader
{
public:
    XmlLoader();
    ~XmlLoader();

protected:
	std::shared_ptr<ptree> LoadXML(std::string xmlFilePath);

private:

};

#endif // XmlLoader_h__