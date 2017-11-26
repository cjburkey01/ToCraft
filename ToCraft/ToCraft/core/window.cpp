#include "window.hpp"

Window::Window() {
}

bool Window::initWindow() {
	exists = false;
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "Failed to initialize GLFW." << std::endl;
		return false;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	
	window = glfwCreateWindow(300, 300, "MichaTest", nullptr, nullptr);
	
	glfwSetWindowSizeCallback(window, onScreenSizeChange);
	glfwSetFramebufferSizeCallback(window, onFrameBufferSizeChange);
	
	if (window == nullptr) {
		std::cout << "Failed to create GLFW Window." << std::endl;
		glfwTerminate();
		return false;
	}
	
	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW." << std::endl;
		glfwTerminate();
		return false;
	}
	
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;
	std::cout << "OpenGL version: " << version << std::endl;
	
	exists = true;
	return true;
}

void Window::destroyWindow() {
	hideWindow();
	glfwDestroyWindow(window);
	exists = false;
}

void Window::showWindow() {
	glfwShowWindow(window);
}

void Window::hideWindow() {
	glfwHideWindow(window);
}

void Window::cleanUp() {
	if (exists) {
		destroyWindow();
	}
	glfwTerminate();
}

void Window::beginRender() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::finishRender() {
	glfwPollEvents();
	glfwSwapBuffers(window);
}

bool Window::doesWindowExist() {
	return exists;
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

int Window::getWidth() {
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	return width;
}

int Window::getHeight() {
	int width;
	int height;
	glfwGetWindowSize(window, &width, &height);
	return height;
}

int Window::getScreenWidth() {
	int sWidth;
	int sHeight;
	glfwGetFramebufferSize(window, &sWidth, &sHeight);
	return sWidth;
}

int Window::getScreenHeight() {
	int sWidth;
	int sHeight;
	glfwGetFramebufferSize(window, &sWidth, &sHeight);
	return sHeight;
}

void Window::setHalfSize() {
	const GLFWvidmode* vidmode = getVidMode();
	glfwSetWindowSize(window, vidmode -> width / 2, vidmode -> height / 2);
}

void Window::centerOnScreen() {
	const GLFWvidmode* vidmode = getVidMode();
	glfwSetWindowPos(window, (vidmode -> width - getScreenWidth()) / 2, int (vidmode -> height - getScreenHeight()) / 2);
}

void Window::onScreenSizeChange(GLFWwindow* window, int width, int height) {
	std::cout << "Setting window size to: (" << width << ',' << ' ' << height << ')' << std::endl;
}

void Window::onFrameBufferSizeChange(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	std::cout << "Setting framebuffer size to: (" << width << ',' << ' ' << height << ')' << std::endl;
}

const GLFWvidmode* Window::getVidMode() {
	return glfwGetVideoMode(glfwGetPrimaryMonitor());
}
