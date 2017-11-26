#define GLEW_STATIC

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.hpp"
#include "shader.hpp"
#include "program.hpp"

Window window;

int main() {
	std::cout << "Launching ToCraft." << std::endl;
	
	window = Window();
	window.initWindow();
	window.setHalfSize();
	window.centerOnScreen();
	window.showWindow();
	
	Shader vertexShader = Shader("resources/shader/basic.vs", GL_VERTEX_SHADER);
	if (!vertexShader.create()) {
		std::cout << "Vertex shader couldn't be created" << std::endl;
		return -1;
	}
	Shader fragmentShader = Shader("resources/shader/basic.fs", GL_FRAGMENT_SHADER);
	if (!fragmentShader.create()) {
		std::cout << "Fragment shader couldn't be created" << std::endl;
		return -1;
	}
	
	shader_list shaders;
	shaders.push_back(vertexShader);
	shaders.push_back(fragmentShader);
	ShaderProgram shaderProgram = ShaderProgram(shaders);
	
	shaderProgram.attach();
	if (!shaderProgram.link()) {
		window.cleanUp();
		return -2;
	}
	shaderProgram.bind();
	
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,	// Bottom Left
		0.5f, -0.5f, 0.0f,	// Bottom Right
		0.0f, 0.5f, 0.0f,	// Top Middle
	};
	
	GLuint vbo;
	GLuint vao;
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(0);
	
	shaderProgram.unbind();
	
	while (!window.shouldClose()) {
		window.beginRender();
		
		shaderProgram.bind();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		shaderProgram.unbind();
		
		window.finishRender();
	}
	
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	
	shaderProgram.unbind();
	
	std::cout << "Closing ToCraft." << std::endl;
	window.cleanUp();
	
	return 0;
}
