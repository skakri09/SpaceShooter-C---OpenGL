#include "VBODrawable.h"
#include "GLUtils/GLUtils.hpp"
using GLUtils::checkGLErrors;

VBODrawable::VBODrawable()
	:log("VBODrawable", WARN)
{
	meshinfoStatus = NO_MESHINFO;
}

VBODrawable::~VBODrawable()
{
}

void VBODrawable::Draw()
{
	if(meshinfoStatus == OBJECT_MESHINFO)
	{
		if(!meshInfo.haveIndices)
		{
			EnableClientStates();

			glDrawArrays(meshInfo.mode, 0, meshInfo.numberOfIndices);
			DisableClientStates();

		}
		else
		{
			EnableClientStates();

			glDrawElements(meshInfo.mode, meshInfo.numberOfIndices, GL_UNSIGNED_INT, 0);

			DisableClientStates();	
		}
	}
	else if(meshinfoStatus == POINTER_MESHINFO)
	{
		if(!meshInfo_p->haveIndices)
		{
			EnableClientStates();

			glDrawArrays(meshInfo_p->mode, 0, meshInfo_p->numberOfIndices);
			DisableClientStates();

		}
		else
		{
			EnableClientStates();

			glDrawElements(meshInfo_p->mode, meshInfo_p->numberOfIndices, GL_UNSIGNED_INT, 0);

			DisableClientStates();	
		}
	}

	else
	{
		log << ERRORX << "meshInfo not set" << std::endl;
	}
	
}

void VBODrawable::SetMeshInfo( MeshInfo meshInfo )
{
	meshInfo_p = &meshInfo;
	//this->meshInfo = meshInfo;
	meshinfoStatus = OBJECT_MESHINFO;
}

void VBODrawable::SetMeshInfo( MeshInfo* meshInfo )
{
	meshInfo_p = meshInfo;
	meshinfoStatus = POINTER_MESHINFO;
}

bool VBODrawable::HaveMeshInfo()
{
	return haveMeshInfo;
}


//  P R I V A T E    F U N C T I O N S  //
//**************************************//

void VBODrawable::EnableClientStates()
{
	if(meshInfo.haveVertices)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.vertices);
		glVertexPointer(3, GL_FLOAT, 0, 0);
	}

	if(meshInfo.haveNormals)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.normals);
		glNormalPointer(GL_FLOAT, 0, 0);
	}

	if(meshInfo.haveColors)
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glBindBuffer(GL_COLOR_ARRAY, meshInfo.colors);
		glColorPointer(3, GL_FLOAT, 0, 0);
	}
	if(meshInfo.haveTexCoords)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, meshInfo.textCoords);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
		glBindTexture(GL_TEXTURE_2D,2); 
	}
	if(meshInfo.haveIndices)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshInfo.indices);
	}
}

void VBODrawable::DisableClientStates()
{
	if(meshInfo.haveVertices)
	{
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	if(meshInfo.haveNormals)
	{
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	if(meshInfo.haveColors)
	{
		glDisableClientState(GL_COLOR_ARRAY);
		glBindBuffer(GL_COLOR_ARRAY, 0);
	}
	if(meshInfo.haveTexCoords)
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D,0); 
	}
	if(meshInfo.haveIndices)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
