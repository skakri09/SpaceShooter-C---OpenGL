#include "VBODrawable.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;

VBODrawable::VBODrawable()
	:log("VBODrawable", WARN)
{
	haveMeshInfo = false;
}

VBODrawable::~VBODrawable()
{

}

void VBODrawable::Draw(bool enableClientStates)
{
	if(haveMeshInfo)
	{
		if(enableClientStates)
			EnableClientStates();
 		if(!meshInfo->haveIndices)
		{
			glDrawArrays(meshInfo->mode, 0, meshInfo->numberOfIndices);
		}
		else
		{
			glDrawElements(meshInfo->mode, meshInfo->numberOfIndices, GL_UNSIGNED_INT, 0);
		}
		if(enableClientStates)
			DisableClientStates();	
	}
	else
	{
		log << ERRORX << "meshInfo not set" << std::endl;
	}
	
}

void VBODrawable::SetMeshInfo( std::shared_ptr<MeshInfo> meshInfo )
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

void VBODrawable::EnableClientStates()
{
	if(meshInfo->haveVertices)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo->vertices);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	}

	if(meshInfo->haveNormals)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo->normals);
		glNormalPointer(GL_FLOAT, 0, 0);
	}

	if(meshInfo->haveColors)
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo->colors);
		glColorPointer(3, GL_FLOAT, 0, 0);
	}
	if(meshInfo->haveTexCoords)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo->textCoords);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
	}
	if(meshInfo->haveIndices)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo->indices);
	}
}

void VBODrawable::DisableClientStates()
{
	if(meshInfo->haveVertices)
	{
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if(meshInfo->haveNormals)
	{
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	if(meshInfo->haveColors)
	{
		glDisableClientState(GL_COLOR_ARRAY);
		glBindBuffer(GL_COLOR_ARRAY, 0);
	}
	if(meshInfo->haveTexCoords)
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if(meshInfo->haveIndices)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
