/********************************************************************
    created:    8:10:2012   9:37
    filename:   MeshLoader.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef MeshLoader_h__
#define MeshLoader_h__

//Disabling a warning that according to various sources
//on the interwebs is faulty and should not appear. Something
//to do with boost. Warning reads as follows:
//Warning	1	warning C4345: behavior change: an object of POD type 
//constructed with an initializer of the form () will be default-initialized

//#pragma warning(disable: 4345)

#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <memory>
#include <vector>
#include "Logger.h"
#include "XmlLoader.h"
#include "NormalCalculator.h"
#include "Mesh.h"
using boost::property_tree::ptree;


//Class used to convert a string
//into a T data type
template <class T>
bool stringToT(T& t, 
	const std::string& s, 
	std::ios_base& (*f)(std::ios_base&))
{
	std::istringstream iss(s);
	return !(iss >> f >> t).fail();
}

class MeshLoader : public XmlLoader
{
public:
    MeshLoader();
    ~MeshLoader();
	
	//Returns a Mesh struct consisting of data from the xml at
	//the loadpath. Loadpath has to contain the full path of
	//the file, including the file name and extension
	std::shared_ptr<Mesh> LoadMeshXml(std::string meshLoadPath);

protected:

private:
	Logger log;

	//NormalCalculator object, the class calculates the normal
	//from a plane in 3D space from the 3 given points
	NormalCalculator normalCalculator;

	//places the param string filled with floats into the param vector as floats
	bool PlaceFloatsInMeshObj(std::string& stringWithFloats, std::vector<float>& targetVector);
	
	//places the param string filled with unsigned ints into the param vector as unsigned ints
	bool PlaceUIntsInMeshObj(std::string& stringWithUInts, std::vector<unsigned int>& targetVector );

	//Places the originString into the targetVector split by spaces
	void GetStringAsVector(std::string& originString, std::vector<std::string>& targetVector);

	//Creates and places normals into the targetVector using the param vertices and indices
	bool MakeNormals(const std::vector<float>& vertices, 
					 const std::vector<unsigned int>& indices,
					 std::vector<float>& targetVector);

};

#endif // MeshLoader_h__