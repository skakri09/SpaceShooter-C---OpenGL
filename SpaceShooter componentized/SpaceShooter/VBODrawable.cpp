#include "VBODrawable.h"


VBODrawable::VBODrawable()
	:log("VBODrawable", WARN)
{
	colorArrayEnabled = false;
	normalArrayEnabled = false;
	vertexArrayEnabled = false;
	elementArrayEnabled = false;
	haveMeshInfo = false;
}

VBODrawable::~VBODrawable()
{
}

void VBODrawable::DrawWithArrays()
{
	if(haveMeshInfo)
	{
		EnableClientStates(false, true, true, false);

		glDrawArrays(meshInfo.mode, 0, meshInfo.numberOfIndices);

		DisableClientStates();
	}
	else
	{
		log << CRITICAL << "meshInfo not set" << std::endl;
	}
}

void VBODrawable::DrawWithIndices()
{
	if(haveMeshInfo)
	{
		EnableClientStates(false, true, true, true);

		glDrawElements(meshInfo.mode, meshInfo.numberOfIndices, GL_UNSIGNED_INT, 0);

		DisableClientStates();	
	}
	else
	{
		log << CRITICAL << "meshInfo not set" << std::endl;
	}
}

void VBODrawable::SetMeshInfo( MeshInfo meshInfo )
{
	this->meshInfo = meshInfo;
	haveMeshInfo = true;
}

bool VBODrawable::HaveMeshInfo()
{
	return haveMeshInfo;
}


//  P R I V A T E    F U N C T I O N S  //
//**************************************//

void VBODrawable::EnableClientStates( bool colorArray /*= false*/, 
										bool normalArray /*= true*/, 
										bool vertexArray /*= true*/, 
										bool elementArray /*= false*/  )
{
	colorArrayEnabled = colorArray;
	normalArrayEnabled = normalArray;
	vertexArrayEnabled = vertexArray;
	elementArrayEnabled = elementArray;

	if(vertexArrayEnabled)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	}

	if(normalArrayEnabled)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
		glNormalPointer(GL_FLOAT, 0, 0);
	}

	if(colorArrayEnabled)
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glBindBuffer(GL_COLOR_ARRAY, meshInfo.colors);
		glColorPointer(3, GL_FLOAT, 0, 0);
	}
	if(elementArrayEnabled)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
	}
}

void VBODrawable::DisableClientStates()
{
	if(vertexArrayEnabled)
	{
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		vertexArrayEnabled = false;
	}
	if(normalArrayEnabled)
	{
		glDisableClientState(GL_NORMAL_ARRAY);
		normalArrayEnabled = false;
	}
	if(colorArrayEnabled)
	{
		glDisableClientState(GL_COLOR_ARRAY);
		glBindBuffer(GL_COLOR_ARRAY, 0);
		colorArrayEnabled = false;
	}
	if(elementArrayEnabled)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		elementArrayEnabled = false;
	}
}
