#ifndef _GLUTILS_HPP__
#define _GLUTILS_HPP__

#include <Windows.h>
#include <GL/GL.h>
#include <gl/GLU.h>

#include <cstdlib>
#include <sstream>
#include <vector>
#include <assert.h>
#include <iostream>
#include <fstream>

namespace GLUtils {
	
inline void checkGLErrors() {
	GLenum ASSERT_GL_err = glGetError(); 
    if( ASSERT_GL_err != GL_NO_ERROR ) { 
		std::stringstream ASSERT_GL_string; 
		ASSERT_GL_string << __FILE__ << '@' << __LINE__ << ": OpenGL error:" 
             << std::hex << ASSERT_GL_err << " " << gluErrorString(ASSERT_GL_err); 
			 throw std::runtime_error( ASSERT_GL_string.str() ); 
    } 
}

}; //Namespace GLUtils

#endif