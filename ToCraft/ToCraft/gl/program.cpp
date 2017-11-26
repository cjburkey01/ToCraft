#include "program.hpp"

ShaderProgram::ShaderProgram(shader_list shaders) {
	program = glCreateProgram();
	this -> shaders = shaders;
}

bool ShaderProgram::attach() {
	std::cout << "Attaching " << shaders.size() << " shaders to the shader program." << std::endl;
	for (int i = 0; i < shaders.size(); i ++) {
		glAttachShader(program, shaders[i].getShader());
	}
	return true;
}

bool ShaderProgram::link() {
	glLinkProgram(program);
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Failed to link shader program:" << std::endl << infoLog << std::endl;
		return false;
	}
	for (int i = 0; i < shaders.size(); i ++) {
		glDeleteShader(shaders[i].getShader());
	}
	return true;
}

GLuint ShaderProgram::getProgram() {
	return program;
}

void ShaderProgram::bind() {
	glUseProgram(program);
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}
