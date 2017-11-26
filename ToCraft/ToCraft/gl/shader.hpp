#ifndef shader_hpp
#define shader_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <stdio.h>

class Shader {
	
public:
	Shader(std::string sourceFile, int type);	// Create the shader from the source file path provided as the provided type.
	bool create();								// Initialize the shader, return true on success, false on failure.
	GLuint getShader();							// Get the shader.
	
private:
	GLuint shader;								// The shader.
	
};

#endif
