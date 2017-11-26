#ifndef program_hpp
#define program_hpp

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <stdio.h>
#include "shader.hpp"

typedef std::vector<Shader> shader_list;

class ShaderProgram {
	
public:
	ShaderProgram(shader_list shaders);	// Create the shader program with the given list of shaders.
	bool attach();						// Attach the shaders/
	bool link();						// Link the program and destroy the shaders.
	GLuint getProgram();				// Return the program.
	void bind();						// Bind the program.
	void unbind();						// Unbind the program.
	
private:
	GLuint program;						// The program.
	shader_list shaders;				// The list of shaders.
	
};

#endif
