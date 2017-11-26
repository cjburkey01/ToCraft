#include "shader.hpp"

Shader::Shader(std::string filePath, int type) {
	std::string shaderCode;
	std::ifstream srcFile(filePath);
	srcFile.exceptions(std::ifstream::badbit);
	try {
		std::stringstream shaderStream;
		shaderStream << srcFile.rdbuf();
		srcFile.close();
		shaderCode = shaderStream.str();
	} catch (std::ifstream::failure e) {
		std::cout << "Failed to load shader source from file: " << filePath << std::endl;
		return;
	}
	const char* source = shaderCode.c_str();
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
}

bool Shader::create() {
	glCompileShader(shader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader could not be compiled:" << std::endl << infoLog << std::endl;
		return false;
	}
	return true;
}

GLuint Shader::getShader() {
	return shader;
}
